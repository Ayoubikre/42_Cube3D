# Fog of War Feature

## Overview
This implementation adds a complete distance-based visibility limiter (fog of war effect) to the Cube3D game. Walls, floors, and ceilings that are far from the player appear darker, creating a circular limited visibility radius that enhances the game's atmosphere and immersion.

## How It Works

The fog effect is applied during the rendering phase to all visible elements:

1. **Distance Calculation**: 
   - For walls: The distance from the player is calculated in `vars->wall_dist` (corrected for fish-eye effect)
   - For floor/ceiling: Distance is calculated per pixel based on the row position and ray angle

2. **Fog Application**: The `apply_fog()` function in `mandatory/Randering/render_text.c` darkens all colors based on distance:
   - Objects at distance 0 retain 100% of their original color
   - Objects gradually darken as distance increases
   - Objects at or beyond `VISIBLE_DISTANCE` appear completely black

3. **Formula**: `fog_factor = distance / VISIBLE_DISTANCE`
   - The color is multiplied by `(1.0 - fog_factor)` for each RGB channel
   - This creates a linear darkening effect for a smooth fog transition

4. **Floor and Ceiling Rendering**:
   - Each vertical column calculates distance for floor and ceiling pixels
   - Distance formula: `distance = row_distance / cos(ray_angle - player_angle)`
   - This creates a circular fog effect around the player

## Customization

To adjust the visibility distance, modify the `VISIBLE_DISTANCE` constant in `mandatory/includes/Data.h`:

```c
# define VISIBLE_DISTANCE 100  // Change this value
```

### Recommended Values:
- **50**: Very close visibility (claustrophobic, maze-like)
- **100**: Default - moderate visibility
- **200**: Long visibility distance
- **500+**: Minimal fog effect (nearly full visibility)

## Implementation Details

### Files Modified:
1. **mandatory/Randering/render_text.c**:
   - Added `apply_fog()` function for color darkening
   - Added `draw_floor_ceiling_column()` function for floor/ceiling fog rendering
   - Modified `draw_column_pixels()` to apply fog to wall textures

2. **mandatory/Randering/ft_3drendering.c**:
   - Removed uniform `draw_background()` call
   - Added call to `draw_floor_ceiling_column()` in `ft_render_column()`

3. **mandatory/includes/cub3d.h**:
   - Added `apply_fog()` function declaration
   - Added `draw_floor_ceiling_column()` function declaration

4. **mandatory/includes/Data.h**:
   - `VISIBLE_DISTANCE` constant already existed but was unused

### Technical Notes:
- The fog affects walls, floors, AND ceilings (complete fog of war)
- Colors are darkened linearly based on distance
- The alpha channel is preserved
- Floor and ceiling distance is calculated per-pixel for accurate fog
- Creates a circular fog effect around the player
- Minimal performance impact (simple calculations per pixel)

## Visual Effect

With `VISIBLE_DISTANCE = 100`:
- An object at distance 0 is rendered at 100% brightness
- An object at distance 25 is rendered at 75% brightness
- An object at distance 50 is rendered at 50% brightness  
- An object at distance 75 is rendered at 25% brightness
- An object at distance 100+ is completely black

This creates a natural "fog of war" effect where the player has a circular area of visibility around them. Beyond this radius, everything fades to complete darkness - you cannot see the floor, ceiling, or walls until you move closer. This creates a true limited visibility experience.
