/*
exported bignum_add
exported bignum_sub
exported bignum_mul
exported bignum_div
exported bignum_mod
exported bignum_pow
exported bignum_root
*/

function
bignum_add(u, v)
{
	u = Math.abs(u);
	v = Math.abs(v);
	return u + v;
}

function
bignum_sub(u, v)
{
	u = Math.abs(u);
	v = Math.abs(v);
	return u - v;
}

function
bignum_mul(u, v)
{
	u = Math.abs(u);
	v = Math.abs(v);
	return u * v;
}

function
bignum_div(u, v)
{
	u = Math.abs(u);
	v = Math.abs(v);
	return Math.floor(u / v);
}

function
bignum_mod(u, v)
{
	u = Math.abs(u);
	v = Math.abs(v);
	return u % v;
}

function
bignum_pow(u, v)
{
	u = Math.abs(u);
	v = Math.abs(v);
	return Math.pow(u, v);
}

function
bignum_root()
{
	return null;
}

function
bignum_cmp(u, v)
{
	u = Math.abs(u);
	v = Math.abs(v);
	if (u < v)
		return -1;
	if (u > v)
		return 1;
	return 0;
}

function
bignum_gcd(u, v)
{
	var r;
	u = Math.abs(u);
	v = Math.abs(v);
	while (v) {
		r = u % v;
		u = v;
		v = r;
	}
	return u;
}

function
bignum_int(n)
{
	return n;
}

function
bignum_atoi(s)
{
	return parseInt(s);
}

function
bignum_itoa(u)
{
	u = Math.abs(u);
	return u.toFixed(0);
}

function
bignum_copy(u)
{
	u = Math.abs(u);
	return u;
}

function
bignum_iszero(u)
{
	return bignum_equal(u, 0);
}

function
bignum_equal(u, n)
{
	u = Math.abs(u);
	return u == n;
}

function
bignum_odd(u)
{
	u = Math.abs(u);
	return u % 2 == 1;
}

function
bignum_smallnum(u)
{
	u = Math.abs(u);
	if (u < 0x100000000)
		return u;
	else
		return null;
}

function
bignum_float(u)
{
	u = Math.abs(u);
	return u;
}