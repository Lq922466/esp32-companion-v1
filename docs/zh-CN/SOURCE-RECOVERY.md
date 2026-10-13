# 源码查找、保留与选择

[English](../SOURCE-RECOVERY.md) | [中文](SOURCE-RECOVERY.md) | [Español](../es/SOURCE-RECOVERY.md)

[中文资料目录](INDEX.md) · [项目首页](../../README.zh-CN.md)
查找范围包括项目工作区、Documents、桌面、Downloads 和用户目录文件清单。Arduino 库／平台示例与生成的编译文件不计入项目源码。检索到的项目交付中没有找到已有独立红外、触摸或舵机诊断程序，因此本次新增这些测试。这不证明其他磁盘或账户没有副本。

保留 22 份恢复的 `.ino`，包括重复副本和早期 V2。[SOURCE-MANIFEST.json](../../archive/SOURCE-MANIFEST.json) 记录原交付相对位置、归档位置和字节级 SHA256。原文件仅被读取／复制；没有修改原始文件或同步 sources。

选择的最终 V2 来自 `2026-10-13/referenced-chatgpt-conversation-this-is-an-5/outputs/PaperRobotV2/PaperRobotV2.ino`，包含整脸移动、六组表情、yaw／pitch 限幅和 OLED 重试诊断。SHA256 为 `f95854ab6551c3beb8494961c1674d4b094c2d2fffccea68b301bfedeab2e7a0`。选择依据是最新恢复交付及用户所需行为，不证明主控当前烧录的程序与之相同。

V1 备份 SHA256：`57a4d9df3a0edf126e0a2f52362ebdcdbd98fd1127e92ec4bb1a0583ac03e699`。它控制左右两舵机，不应当作 V2 的 yaw／pitch 程序，上传前须检查机械行为。

核对的旧公开仓库为 [Lq922466/esp32-companion-v1](https://github.com/Lq922466/esp32-companion-v1)，更新前快照提交 `b30bdd8`，文件保存在 archive/prior-public-repository。先克隆作参考，后获得用户授权将 V2 发布到同一仓库；快照记录更新前状态。没有修改 INNNX 作品集。

重新编译覆盖所选 V2、V1 和九个可运行诊断程序；其他历史副本保留供比较，不声称全部重新编译。预期行为与实际证据在 [测试记录](TESTING.md) 中分开。
