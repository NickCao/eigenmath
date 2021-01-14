#include "app.h"

void
emit_update_subscript(void)
{
	int font_num;
	double d, dx, dy, h, t, w;

	save();

	p1 = pop();

	t = get_char_width(SMALL_ROMAN_FONT, 'n') / 4.0;

	d = DEPTH(p1);
	w = t + WIDTH(p1);

	if (emit_level == 0)
		font_num = ROMAN_FONT;
	else
		font_num = SMALL_ROMAN_FONT;

	h = get_cap_height(font_num);

	dx = t;
	dy = h / 2.0;

	d += dy;

	push_double(EMIT_SUBSCRIPT);
	push_double(h);
	push_double(d);
	push_double(w);
	push_double(dx);
	push_double(dy);
	push(p1);

	list(7);

	restore();
}
