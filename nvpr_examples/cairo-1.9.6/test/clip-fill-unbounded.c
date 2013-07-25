/*
 * Copyright 2009 Chris Wilson
 *
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose is hereby granted without
 * fee, provided that the above copyright notice appear in all copies
 * and that both that copyright notice and this permission notice
 * appear in supporting documentation, and that the name of
 * Chris Wilson not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission. Chris Wilson makes no representations about the
 * suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * CHRIS WILSON DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL CHRIS WILSON BE LIABLE FOR ANY SPECIAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Author: Chris Wilson <chris@chris-wilson.co.uk>
 */

#include "cairo-test.h"

#define WIDTH 40
#define HEIGHT 40

static void
shapes (cairo_t *cr)
{
    cairo_set_operator (cr, CAIRO_OPERATOR_OVER);
    cairo_set_source_rgb (cr, 1, 0, 0);
    cairo_paint (cr);

    cairo_set_operator (cr, CAIRO_OPERATOR_IN);
    cairo_set_source_rgb (cr, 0, 0.7, 0);
    cairo_new_sub_path (cr);
    cairo_arc (cr, 10, 10, 8.5, 0, 2 * M_PI);
    cairo_new_sub_path (cr);
    cairo_arc_negative (cr, 10, 10, 6.5, 2 * M_PI, 0);
    cairo_set_fill_rule (cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill (cr);
}

static cairo_test_status_t
draw (cairo_t *cr, int width, int height)
{
    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);

    cairo_translate (cr, 10, 10);

    /* simple clip */
    cairo_save (cr);
    cairo_rectangle (cr, 0, 0, 20, 20);
    cairo_clip (cr);
    shapes (cr);
    cairo_restore (cr);

    cairo_translate (cr, WIDTH, 0);

    /* unaligned clip */
    cairo_save (cr);
    cairo_rectangle (cr, 0.5, 0.5, 20, 20);
    cairo_clip (cr);
    shapes (cr);
    cairo_restore (cr);

    cairo_translate (cr, -WIDTH, HEIGHT);

    /* aligned-clip */
    cairo_save (cr);
    cairo_set_fill_rule (cr, CAIRO_FILL_RULE_EVEN_ODD);
    cairo_rectangle (cr, 0, 0, 20, 20);
    cairo_rectangle (cr, 3, 3, 10, 10);
    cairo_rectangle (cr, 7, 7, 10, 10);
    cairo_clip (cr);
    shapes (cr);
    cairo_restore (cr);

    cairo_translate (cr, WIDTH, 0);

    /* force a clip-mask */
    cairo_save (cr);
    cairo_arc (cr, 10, 10, 10, 0, 2 * M_PI);
    cairo_new_sub_path (cr);
    cairo_arc_negative (cr, 10, 10, 5, 2 * M_PI, 0);
    cairo_new_sub_path (cr);
    cairo_arc (cr, 10, 10, 2, 0, 2 * M_PI);
    cairo_clip (cr);
    shapes (cr);
    cairo_restore (cr);

    return CAIRO_TEST_SUCCESS;
}

CAIRO_TEST (clip_fill_unbounded,
	    "Tests unbounded fill through complex clips.",
	    "clip, fill, unbounded", /* keywords */
	    NULL, /* requirements */
	    2 * WIDTH, 2* HEIGHT,
	    NULL, draw)
