function
eval_unit(p1)
{
	var i, j, n;

	push(cadr(p1));
	evalf();

	n = pop_integer();

	if (n < 1)
		stopf("unit: index error");

	if (n == 1) {
		push_integer(1);
		return;
	}

	p1 = alloc_matrix(n, n);

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (i == j)
				p1.elem[n * i + j] = one;
			else
				p1.elem[n * i + j] = zero;

	push(p1);
}
