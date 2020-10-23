function
draw_point(F, X, x, save)
{
	var drawn, p, y, t;

	t = DRAW_WIDTH * (x - xmin) / (xmax - xmin);

	if (t < 0 || t > DRAW_WIDTH)
		return;

	draw_evalf(F, X, x);

	p = pop();

	if (!isdouble(p))
		return;

	y = DRAW_HEIGHT * (1 - (p.d - ymin) / (ymax - ymin));

	if (y < 0 || y > DRAW_HEIGHT)
		drawn = 0;
	else {
		draw_line(t, y, t, y, 2);
		drawn = 1;
	}

	if (save)
		draw_array.push({x:x, y:y, drawn:drawn});
}
