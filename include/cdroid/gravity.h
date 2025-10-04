#ifndef __cdroid_gravity_h__
#define __cdroid_gravity_h__

#include "cdroid/internal/types.h"

CDROID_HEADER_BEGIN

/** Constant indicating that no gravity has been set **/
#define GRAVITY_NO 0x0000

/** Raw bit indicating the gravity for an axis has been specified **/
#define GRAVITY_AXIS_SPECIFIED 0x0001

/** Raw bit controlling how the left/top edge is placed **/
#define GRAVITY_AXIS_PULL_BEFORE 0x0002
/** Raw bit controlling how the right/bottom edge is placed **/
#define GRAVITY_AXIS_PULL_AFTER 0x0004
/** Raw bit controlling whether the right/bottom edge is clipped to its
 * container **/
#define GRAVITY_AXIS_CLIP 0x0008

/** Bits defining the horizontal axis **/
#define GRAVITY_AXIS_X_SHIFT 0
/** Bits defining the vertical axis **/
#define GRAVITY_AXIS_Y_SHIFT 4

/** Push object to the top of its container, not changing its size **/
#define GRAVITY_TOP                                                           \
  ((GRAVITY_AXIS_PULL_BEFORE | GRAVITY_AXIS_SPECIFIED) << GRAVITY_AXIS_Y_SHIFT)
/** Push object to the bottom of its container, not changing its size **/
#define GRAVITY_BOTTOM                                                        \
  ((GRAVITY_AXIS_PULL_AFTER | GRAVITY_AXIS_SPECIFIED) << GRAVITY_AXIS_Y_SHIFT)

/** Push object to the left of its container, not changing its size **/
#define GRAVITY_LEFT                                                          \
  ((GRAVITY_AXIS_PULL_BEFORE | GRAVITY_AXIS_SPECIFIED) << GRAVITY_AXIS_X_SHIFT)
/** Push object to the right of its container, not changing its size **/
#define GRAVITY_RIGHT                                                         \
  ((GRAVITY_AXIS_PULL_AFTER | GRAVITY_AXIS_SPECIFIED) << GRAVITY_AXIS_X_SHIFT)

/** Place object in the vertical center of its container, not changing its size
 * **/
#define GRAVITY_CENTER_VERTICAL                                               \
  (GRAVITY_AXIS_SPECIFIED << GRAVITY_AXIS_Y_SHIFT)
/** Place object in the horizontal center of its container, not changing its
 * size **/
#define GRAVITY_CENTER_HORIZONTAL                                             \
  (GRAVITY_AXIS_SPECIFIED << GRAVITY_AXIS_X_SHIFT)
/** Place the object in the center of its container in both axes **/
#define GRAVITY_CENTER (GRAVITY_CENTER_VERTICAL | GRAVITY_CENTER_HORIZONTAL)

/** Grow the vertical size of the object if needed so it completely fills its
 * container **/
#define GRAVITY_FILL_VERTICAL (GRAVITY_TOP | GRAVITY_BOTTOM)
/** Grow the horizontal size of the object if needed so it completely fills its
 * container **/
#define GRAVITY_FILL_HORIZONTAL (GRAVITY_LEFT | GRAVITY_RIGHT)
/** Grow the horizontal and vertical size of the object if needed so it
 * completely fills its container **/
#define GRAVITY_FILL (GRAVITY_FILL_VERTICAL | GRAVITY_FILL_HORIZONTAL)

/** Flag to clip the edges of the object to its container along the vertical
 * axis **/
#define GRAVITY_CLIP_VERTICAL (GRAVITY_AXIS_CLIP << GRAVITY_AXIS_Y_SHIFT)
/** Flag to clip the edges of the object to its container along the horizontal
 * axis **/
#define GRAVITY_CLIP_HORIZONTAL (GRAVITY_AXIS_CLIP << GRAVITY_AXIS_X_SHIFT)

/** Raw bit controlling whether the layout direction is relative or not
 * (START/END instead of LEFT/RIGHT) **/
#define GRAVITY_RELATIVE_LAYOUT_DIRECTION 0x00800000

/** Binary mask to get the absolute horizontal gravity of a gravity **/
#define GRAVITY_HORIZONTAL_MASK                                               \
  ((GRAVITY_AXIS_SPECIFIED | GRAVITY_AXIS_PULL_BEFORE                         \
    | GRAVITY_AXIS_PULL_AFTER)                                                \
   << GRAVITY_AXIS_X_SHIFT)
/** Binary mask to get the vertical gravity of a gravity **/
#define GRAVITY_VERTICAL_MASK                                                 \
  ((GRAVITY_AXIS_SPECIFIED | GRAVITY_AXIS_PULL_BEFORE                         \
    | GRAVITY_AXIS_PULL_AFTER)                                                \
   << GRAVITY_AXIS_Y_SHIFT)

/** Special constant to enable clipping to an overall display along the
 * vertical dimension **/
#define GRAVITY_DISPLAY_CLIP_VERTICAL 0x10000000
/** Special constant to enable clipping to an overall display along the
 * horizontal dimension **/
#define GRAVITY_DISPLAY_CLIP_HORIZONTAL 0x01000000

/** Push object to x-axis position at the start of its container, not changing
 * its size **/
#define GRAVITY_START (GRAVITY_RELATIVE_LAYOUT_DIRECTION | GRAVITY_LEFT)
/** Push object to x-axis position at the end of its container, not changing
 * its size **/
#define GRAVITY_END (GRAVITY_RELATIVE_LAYOUT_DIRECTION | GRAVITY_RIGHT)

/** Binary mask for the horizontal gravity and script specific direction bit
 * **/
#define GRAVITY_RELATIVE_HORIZONTAL_MASK (GRAVITY_START | GRAVITY_END)

CDROID_HEADER_END

#endif