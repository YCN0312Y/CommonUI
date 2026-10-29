# UIDemo · CommonUI 学习项目

UIDemo 是一个基于 **Unreal Engine 5.3、CommonUI 和 UnLua** 的游戏前端 UI 学习与实践项目。项目使用 C++、UMG 蓝图和 Lua，围绕主菜单、设置页面、确认弹窗和加载界面，实践 CommonUI 的页面管理、输入交互与通用控件封装。

项目重点是构建可复用的 UI 结构：通过子系统统一管理界面，通过控件栈组织页面层级，通过数据对象驱动设置列表，并将底层逻辑、界面表现和交互流程分开维护。

## 主要功能

- **菜单交互**：按任意键进入，提供故事、选项、关于和退出入口，以及按钮悬停描述和返回操作。
- **界面管理**：按层级组织页面，支持界面资源异步加载与通用确认弹窗。
- **设置页面**：包含游戏玩法、音频、视频和控制四类设置，提供选项切换、滑块调节、详情展示和恢复默认功能。
- **设置与输入**：管理用户设置，支持键盘/鼠标按键重映射及保存。
- **加载与表现**：提供加载界面、加载状态提示，以及菜单页面之间的摄像机过渡。

## 技术栈

| 技术 | 主要用途 |
| --- | --- |
| Unreal Engine 5.3 | 项目运行与开发环境 |
| C++ | 子系统、通用控件、设置数据模型与核心逻辑 |
| UMG / 蓝图 | 界面布局、动画、样式与资源配置 |
| CommonUI / CommonInput | 页面激活、控件容器、按钮、列表、标签页及 UI 输入支持 |
| UnLua / Lua | 菜单事件、界面流程与摄像机切换 |
| Enhanced Input | 玩家输入映射与按键重映射 |
| Gameplay Tags | 标识界面资源与控件层级 |
| Data Asset / Developer Settings | 控件类型映射与项目级 UI 配置 |
| Game User Settings | 用户设置的读写、应用与保存 |

## 使用到的 CommonUI 类

项目在 CommonUI 基础类之上封装了带有 `YCN` 前缀的控件，并在蓝图中配置具体的布局和样式。

| CommonUI 类 | 项目中的使用方式 |
| --- | --- |
| `UCommonUserWidget` | 作为主布局 `UYCNWidget_MainLayout` 和设置列表条目基类的基础 |
| `UCommonActivatableWidget` | 封装为 `UYCNWidget_ActivatableBase`，为设置页、确认弹窗和按键重映射弹窗提供统一的可激活页面基础 |
| `UCommonActivatableWidgetContainerBase` | 作为主布局中各层控件容器的统一接口，用于查找目标层并添加页面 |
| `UCommonButtonBase` | 封装为 `UYCNCommonButtonBase`，统一按钮文字、图片、文本样式与悬停描述 |
| `UCommonTabListWidgetBase` | 封装为 `UYCNTabListWidgetBase`，管理设置页面的分类标签与切换 |
| `UCommonListView` | 封装为 `UYCNCommonListViewBase`，根据设置数据展示对应的列表条目 |
| `UCommonRotator` | 封装为 `UYCNCommonRotatorBase`，用于游戏难度等离散选项的轮换显示 |
| `UCommonTextBlock` / `UCommonRichTextBlock` | 显示按钮文字、页面标题、设置说明和详情信息 |
| `UCommonNumericTextBlock` | 显示滑块对应的数值与百分比 |
| `UCommonLazyImage` | 显示按钮图片、按键图标与设置详情图片 |
| `UCommonGameViewportClient` | 作为项目的游戏视口客户端，接入 CommonUI 输入路由 |

输入部分同时使用 CommonInput 的 `UCommonInputSubsystem` 和平台输入配置，配合按键图标展示；实际按键重映射由 Enhanced Input 的用户设置系统负责。

## 项目架构

### 界面管理与分层

`UYCNWidgetSubsystem` 负责统一管理主布局、异步加载界面和创建确认弹窗。主布局 `UYCNWidget_MainLayout` 保存各层控件容器，通过 Gameplay Tags 将页面放入对应层级。

主布局预设四个层级：

| 层级 | 职责 |
| --- | --- |
| `Frontend` | 主菜单及前端页面 |
| `GameHUD` | 预留游戏内 HUD 层 |
| `GameMenu` | 预留游戏内菜单层 |
| `Modal` | 确认窗口等模态弹窗 |

页面资源通过软引用配置，并由异步操作连接蓝图、Lua 与界面管理子系统。页面本身基于统一的可激活控件基类，便于复用返回和生命周期相关行为。

### 数据驱动的设置系统

设置页面采用“**数据注册表 → 数据对象 → 列表条目**”的组织方式。

`UYCNOptionsDataRegistry` 统一组织游戏玩法、音频、视频和控制分类。各设置项由独立的数据对象描述，保存显示名称、说明、默认值以及对应的设置读写关系；列表根据数据类型选择合适的控件，展示选项轮换、滑块或按键修改入口。

数据与控件分开后，同一类条目可以用于多个设置项。详情展示、恢复默认和设置项之间的关联更新也围绕数据对象组织，减少各页面中重复的处理逻辑。

### C++、蓝图与 Lua 协作

- **C++**：封装稳定的基础能力，包括界面管理、数据模型、通用控件和设置读写。
- **UMG 蓝图**：组合控件，配置界面布局、字体、图片、动画及资源引用。
- **Lua**：连接菜单按钮事件和页面流程，处理主布局注册、入口交互及菜单镜头切换。

### 加载界面与用户设置

加载界面由独立的 `UYCNLoadingScreenSubsystem` 管理，结合地图加载和世界就绪状态控制显示，并向相关对象发送状态通知。

普通设置由 `UYCNGameUserSettings` 管理，按键映射由 Enhanced Input 用户设置管理。两者通过设置数据对象接入页面，使界面展示与具体配置存储保持相对独立。

## 主要目录

| 目录 | 内容 |
| --- | --- |
| `Source/UIDemo/Subsystems` | 界面管理与加载界面子系统 |
| `Source/UIDemo/Widgets` | 主布局、CommonUI 扩展控件、页面和设置数据模型 |
| `Source/UIDemo/Async` | 界面加载与弹窗异步操作 |
| `Source/UIDemo/Settings` | 用户设置与项目 UI 配置 |
| `Content/UI` | UMG 蓝图与界面资源 |
| `Content/Script` | UnLua 脚本 |
| `Config` | 默认地图、输入和项目配置 |

项目默认演示地图为 `/Game/Maps/L_UIMap`，主要用于学习和展示游戏前端 UI 架构与交互流程。
