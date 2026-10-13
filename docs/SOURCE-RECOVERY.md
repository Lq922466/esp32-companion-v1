# Source recovery and selection

[中文](zh-CN/SOURCE-RECOVERY.md) | [Español](es/SOURCE-RECOVERY.md)
The recovery search covered the project workspace, Documents, Desktop, Downloads and user-home indexed file inventory. Arduino library/platform examples and generated build files were excluded from the project-source inventory. No existing standalone IR, touch or servo diagnostic sketch was found in the searched project deliveries; those tests were authored for this package. This is not proof that no other copy exists on another drive or account.

22 recovered project `.ino` files are retained, including duplicate copies and earlier V2 revisions. SOURCE-MANIFEST.json records original delivery-relative locations, archive locations and byte-level SHA256 hashes. Original files were read/copied; no originals or synced `sources/` were modified.

The selected final V2 is the `2026-10-13/referenced-chatgpt-conversation-this-is-an-5/outputs/PaperRobotV2/PaperRobotV2.ino` delivery: it includes whole-face movement, six-pose geometry, yaw/pitch limits and OLED retry diagnostics. Its SHA256 is `f95854ab6551c3beb8494961c1674d4b094c2d2fffccea68b301bfedeab2e7a0`. Selection is based on the latest recovered delivery and requested behavior, not proof of the currently flashed board contents.

Selected V1 backup SHA256: `57a4d9df3a0edf126e0a2f52362ebdcdbd98fd1127e92ec4bb1a0583ac03e699`. It controls two left/right servos; it should not be treated as the V2 yaw/pitch sketch or uploaded without inspecting its mechanical behavior.

The existing public repository inspected was [Lq922466/esp32-companion-v1](https://github.com/Lq922466/esp32-companion-v1), snapshot commit `b30bdd8`. Its files remain under archive/prior-public-repository. It was cloned for reference before the owner authorized updating this same repository with the V2 package. The snapshot records its pre-update contents. No INNNX portfolio files were modified.

Fresh compilation covers the selected V2, selected V1 and nine runnable diagnostic sketches. Other recovered historical copies are preserved for comparison and are not claimed to have been recompiled. Expected hardware behavior is documented separately from observed test evidence.
