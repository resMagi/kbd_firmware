# KBD firmware

Forked from [foostan/kbd_firmware](https://github.com/foostan/kbd_firmware).

This fork adds a custom keymap (`magi`) inspired by [NeoQWERTZ](https://www.neo-layout.org/Layouts/neoqwertz/) for the Corne 4.1 (crkbd) keyboard with:

- German QWERTZ base layout with dedicated Ö, Ä, Ü keys
- **Automatic OS detection** — switches between macOS and Linux/Windows keycodes at boot (no manual toggle needed)
- Symbol layer optimized for programming
- Navigation layer with arrow keys, Page Up/Down, Home/End
- F-key layer with RGB controls

The layout also contains a completely custom per-key RGB lighting with spiral LED mapping. Each key can be mapped to a specific color.

## Custom keymap: `magi`

### Building

```sh
make vial-qmk-clean
kb=crkbd make vial-qmk-init
kb=crkbd kr=rev4_1/standard km=magi make vial-qmk-compile
```

Firmware will be in `keyboards/crkbd/vial-kb/vial-qmk/.build/`

### Layer overview

| Layer | Purpose              | Key highlights                         |
| ----- | -------------------- | -------------------------------------- |
| 0     | Base (QWERTZ)        | Letters, Umlauts (Ö, Ä), -, Repeat Key |
| 1     | Symbols              | @, [], {}, \|, ~, /, !, <, >, =, etc.  |
| 2     | Navigation + Numbers | Arrows, PgUp/Dn, Home/End, 0-9         |
| 3     | F-Keys + System      | F1-F12, RGB toggle, QK_BOOT            |

Note: On layer 3 are some macro keys, which are used to navigate workspaces with [AeroSpace](https://github.com/nikitabobko/AeroSpace).

### OS Detection

The keymap uses QMK's [OS Detection](https://docs.qmk.fm/features/os_detection) feature. Only 8 symbol keycodes differ between macOS and Linux/Windows (e.g. `@`, `\`, `[`, `]`, `{`, `}`, `|`, `~`). All other keys are identical across platforms.

No separate keymaps or manual switching required.

---

## Original build instructions (from foosta)

### 1. Setting Up Your QMK Environment

Please see https://docs.qmk.fm/#/newbs_getting_started and set up 1 to 3.

### 2. Getting source files

Please get source files of `qmk/qmk_firmware` and `vial-kb/vial-qmk`

```sh
make git-submodule
```

### 3. Building firmwares

#### for VIA

```sh
make qmk-clean
kb=crkbd make qmk-init
kb=crkbd kr=rev4_1/standard km=via make qmk-compile
```

A built data will be stored on `keyboards/crkbd/qmk/qmk_firmware/.build`
Please change `kb`, `kr` and `km` when build other.

#### for Vial

```sh
make vial-qmk-clean
kb=crkbd make vial-qmk-init
kb=crkbd kr=rev4_1/standard km=vial make vial-qmk-compile
```

A built data will be stored on `keyboards/crkbd/vial-kb/vial-qmk/.build`
Please change `kb`, `kr` and `km` when build other.

#### All cleaning and building

```sh
make update-all
```
