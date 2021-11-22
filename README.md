
[Eigenmath Manual](https://georgeweigt.github.io/eigenmath.pdf)

# eigenmath.c

To build and run

```
make
./eigenmath
```

Press ctrl-C to exit.

Eigenmath uses UTF-8 encoding. The terminal window should have UTF-8 enabled.

To run a script

```
./eigenmath scriptfilename
```

Sample scripts are available at [georgeweigt.github.io](https://georgeweigt.github.io)

To run test scripts

```
./eigenmath test/selftest1
./eigenmath test/selftest2
```

If something goes wrong, "stop" is printed.
Otherwise, all good.

To generate LaTeX output

```
./eigenmath --latex scriptfilename | tee foo.tex
```

To generate MathML output

```
./eigenmath --mathml scriptfilename | tee foo.html
```

To generate MathJax output

```
./eigenmath --mathjax scriptfilename | tee foo.html
```

To build eigenmath.c

```
cd tools
make eigenmath.c
```

# eigenmath.js

eigenmath.js is a Javascript file that can evaluate an Eigenmath script.

Script is read from `document.getElementById("stdin").value`

Results are written to `document.getElementById("stdout").innerHTML`

For example (click [here](https://georgeweigt.github.io/demo.html) to run)

```html
<html>
<body>

<script src="https://georgeweigt.github.io/eigenmath.js"></script>

<textarea id="stdin" rows="24" cols="80" style="font-family:courier;font-size:12pt">
-- Eigenmath script goes here, for example
f = sin(x) / x
f
draw(f,x)

</textarea>

<button onclick="run()" style="font-size:20pt">Run</button>

<p>
<div id="stdout"></div>

</body>
</html>
```

To build eigenmath.js

```
cd js
make
```
