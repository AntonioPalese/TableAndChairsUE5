# TableAndChairs

A procedural furniture generator built in **Unreal Engine 5.3**. The project synthesizes tables and matching sets of chairs at runtime, generating each piece's geometry with **Procedural Mesh Component** meshes rather than static assets, while exposing every dimensional parameter to designers through Blueprint.

## Overview

TableAndChairs demonstrates a hybrid C++/Blueprint architecture for procedural content generation:

- **C++ core** — handles mesh construction and geometric composition. Primitive `Cuboid` and `Rectangle` building blocks are assembled into `Table` and `Chair` objects, which are combined and positioned by the `ATableAndChairsActor`.
- **Blueprint layer** — drives user input, parameter randomization, and GUI management, letting designers regenerate furniture sets interactively without touching code.

Each `Regenerate()` call produces a new, internally consistent table-and-chair set: leg heights, top dimensions, seat sizes, and back heights are all randomized within engineering-sound constraints so that generated furniture remains proportionate and structurally plausible.

## Requirements

- Unreal Engine **5.3**
- The **ProceduralMeshComponent** and **ModelingToolsEditorMode** plugins (declared in `TableAndChairs.uproject`)

## Getting Started

1. Clone the repository.
2. Right-click `TableAndChairs.uproject` and select **Generate Visual Studio project files** (or open directly in the Unreal Editor).
3. Open the project in Unreal Engine 5.3.
4. Place a `TableAndChairsActor` in a level and use its exposed Blueprint properties, or call `Regenerate()`, to generate a new table and chair set.

## Generation Parameters

Furniture dimensions (in centimeters) are randomized within the ranges below to guarantee structurally coherent results.

### Table

| Parameter | Description | Range |
|---|---|---|
| `HTlegs` | Table leg height | `[80.0, 120.0]` |
| `Wttop` | Table top width | `[200.0, 800.0]` |
| `Lttop` | Table top length | `[200.0, 800.0]` |
| `Httop` | Table top height | `[10.0, 30.0]` |

### Chair

| Parameter | Description | Range |
|---|---|---|
| `Wseat` | Chair seat width | `[30.0, 120.0]` |
| `Lseat` | Chair seat length | `[30.0, 120.0]` |
| `Hseat` | Chair seat height | `[5.0, 20.0]` |
| `Hlegs` | Chair leg height | `[60.0, (HTlegs - HTlegs / 3) - Hseat]` |
| `Hback` | Chair back height | `[30.0, 100.0]` |

Chair leg height is deliberately constrained relative to the table's leg height, ensuring generated chairs always sit correctly beneath the table.

### Fixed Parameters

For visual consistency, the following dimensions are hardcoded rather than randomized:

- Table leg width and length: `5.0`
- Chair leg width and length: `5.0`
- Chair back thickness: `5.0`
- Chair back width: fixed to chair seat width

## Project Structure

```
Source/TableAndChairs/
├── Public/            # Class declarations
│   ├── Cuboid.h            # Base geometric primitive
│   ├── Rectangle.h         # Base geometric primitive
│   ├── Table.h             # Table composition and mesh generation
│   ├── Chair.h             # Chair composition and mesh generation
│   ├── TableAndChairsActor.h   # Actor exposing parameters and Regenerate()
│   ├── TCCameraController.h    # Scene camera control
│   └── TableAndChairsGameModeBase.h
└── Private/            # Implementations
```

A standalone Python prototype (`draw.py`, `draw_from_file.py`) is included for visualizing and validating the generation logic outside of Unreal Engine using `matplotlib`.

## License

No license has been specified for this project.
