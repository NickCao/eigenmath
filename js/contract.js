function
contract()
{
	var h, i, j, k, m, n, ncol, ndim, nelem, nrow;
	var index = [];

	p3 = pop();
	p2 = pop();
	p1 = pop();

	if (!istensor(p1))
		stop("contract: 1st arg is not a tensor");

	ndim = p1.dim.length;

	push(p2);
	n = pop_integer();

	push(p3);
	m = pop_integer();

	if (n < 1 || n > ndim)
		stop("contract: 2nd arg not numerical or out of range (less than 1 or greater than tensor rank)");

	if (m < 1 || m > ndim)
		stop("contract: 3rd arg not numerical or out of range (less than 1 or greater than tensor rank)");

	if (n == m)
		stop("contract: 2nd and 3rd args are the same");

	n--; // make zero based
	m--;

	ncol = p1.dim[n];
	nrow = p1.dim[m];

	if (ncol != nrow)
		stop("contract: unequal tensor dimensions for indices given by 2nd and 3rd args");

	// nelem is the number of elements in result

	nelem = p1.elem.length / ncol / nrow;

	p2 = alloc_tensor();

	for (i = 0; i < ndim; i++)
		index[i] = 0;

	for (i = 0; i < nelem; i++) {

		for (j = 0; j < ncol; j++) {
			index[n] = j;
			index[m] = j;
			k = index[0];
			for (h = 1; h < ndim; h++)
				k = k * p1.dim[h] + index[h];
			push(p1.elem[k]);
		}

		add_terms(ncol);

		p2.elem[i] = pop();

		// increment index

		for (j = ndim - 1; j >= 0; j--) {
			if (j == n || j == m)
				continue;
			if (++index[j] < p1.dim[j])
				break;
			index[j] = 0;
		}
	}

	if (nelem == 1) {
		push(p2.elem[0]);
		return;
	}

	// add dim info

	k = 0;

	for (i = 0; i < ndim; i++)
		if (i != n && i != m)
			p2.dim[k++] = p1.dim[i];

	push(p2);
}