# Fog of War Feature

## Overview
This implementation adds a distance-based visibility limiter (fog of war effect) to the Cube3D game. Walls that are far from the player appear darker, creating a limited visibility radius that enhances the game's atmosphere.

## How It Works

The fog effect is applied during the rendering phase:

1. **Distance Calculation**: For each wall column being rendered, the distance from the player is already calculated in `vars->wall_dist` (corrected for fish-eye effect).

2. **Fog Application**: The `apply_fog()` function in `mandatory/Randering/render_text.c` darkens the wall texture colors based on distance:
   - Walls at distance 0 retain 100% of their original color
   - Walls gradually darken as distance increases
   - Walls at or beyond `VISIBLE_DISTANCE` appear completely black

3. **Formula**: `fog_factor = distance / VISIBLE_DISTANCE`
   - The color is multiplied by `(1.0 - fog_factor)` for each RGB channel
   - This creates a linear darkening effect

## Customization

To adjust the visibility distance, modify the `VISIBLE_DISTANCE` constant in `mandatory/includes/Data.h`:

```c
# define VISIBLE_DISTANCE 100  // Change this value
```

### Recommended Values:
- **50**: Very close visibility (claustrophobic)
- **100**: Default - moderate visibility
- **200**: Long visibility distance
- **500+**: Minimal fog effect

## Implementation Details

### Files Modified:
1. **mandatory/Randering/render_text.c**:
   - Added `apply_fog()` function
   - Modified `draw_column_pixels()` to apply fog to each pixel

2. **mandatory/includes/cub3d.h**:
   - Added `apply_fog()` function declaration

3. **mandatory/includes/Data.h**:
   - `VISIBLE_DISTANCE` constant already existed but was unused

### Technical Notes:
- The fog only affects wall rendering, not floor/ceiling
- Colors are darkened linearly based on distance
- The alpha channel is preserved
- No performance impact as it's a simple multiplication per pixel

## Example

With `VISIBLE_DISTANCE = 100`:
- A wall at distance 25 is rendered at 75% brightness
- A wall at distance 50 is rendered at 50% brightness  
- A wall at distance 75 is rendered at 25% brightness
- A wall at distance 100+ is completely black

This creates a natural "fog of war" effect where the player can only see clearly in their immediate vicinity, and distant areas fade to black.
