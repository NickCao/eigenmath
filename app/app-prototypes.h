int check_display(void);
void clear_display(void);
void cmdisplay(void);
int count_denominators(struct atom *p);
void draw_char(double x, double y, int font_num, int char_num);
void draw_display(double ymin, double ymax);
void draw_display_nib(struct display *p, double y, double ymin, double ymax);
void draw_formula(double x, double y, float *p);
void draw_point(double x, double y);
void draw_selection_rect(double x, double y, double width, double height);
void draw_stroke(double x1, double y1, double x2, double y2, double stroke_width);
void draw_text(double x, double y, uint8_t *buf, int len);
void echo_input(char *s);
void emit_args(struct atom *p);
void emit_base(struct atom *p);
void emit_box(void);
void emit_denominators(struct atom *p);
void emit_double(struct atom *p);
void emit_draw(double x, double y, struct atom *p);
void emit_draw_delims(double x, double y, double h, double d, double w, double stroke_width, int font_num);
void emit_draw_ldelim(double x, double y, double h, double d, double w, double stroke_width);
void emit_draw_rdelim(double x, double y, double h, double d, double w, double stroke_width);
void emit_draw_table(double x, double y, struct atom *p);
void emit_exponent(struct atom *p);
void emit_expr(struct atom *p);
void emit_expr_nib(struct atom *p);
void emit_factor(struct atom *p);
void emit_frac(struct atom *p);
void emit_function(struct atom *p);
void emit_graph(void);
void emit_indices(struct atom *p);
void emit_infix_operator(int c);
void emit_italic_char(int char_num);
void emit_italic_string(char *s);
void emit_labels(void);
void emit_list(struct atom *p);
void emit_matrix(struct atom *p, int d, int k);
void emit_medium_space(void);
void emit_numerators(struct atom *p);
void emit_numeric_exponent(struct atom *p);
void emit_power(struct atom *p);
void emit_push(double d);
void emit_rational(struct atom *p);
void emit_reciprocal(struct atom *p);
void emit_roman_char(int char_num);
void emit_roman_string(char *s);
void emit_string(struct atom *p);
void emit_subexpr(struct atom *p);
void emit_symbol(struct atom *p);
int emit_symbol_fragment(char *s, int k);
void emit_tensor(struct atom *p);
void emit_term(struct atom *p);
void emit_term_nib(struct atom *p);
void emit_text(char *buf, int len, int color);
void emit_thick_space(void);
void emit_thin_space(void);
void emit_update_fraction(void);
void emit_update_list(int t);
void emit_update_subexpr(void);
void emit_update_subscript(void);
void emit_update_superscript(void);
void emit_update_table(int n, int m);
void emit_vector(struct atom *p);
void emit_xaxis(void);
void emit_yaxis(void);
void eval_draw(void);
void draw_main(void);
void check_for_parametric_draw(void);
void create_point_set(void);
void new_point(double t);
void get_xy(double t);
void eval_f(double t);
int invisible(int i);
void fill(int i, int j);
void setup_trange(void);
void setup_trange_nib(void);
void setup_xrange(void);
void setup_xrange_nib(void);
void setup_yrange(void);
void setup_yrange_nib(void);
void eval_exit(void);
double get_ascent(int font_num);
double get_cap_height(int font_num);
double get_char_depth(int font_num, int char_num);
CFStringRef get_char_name(int char_num);
double get_char_width(int font_num, int char_num);
double get_descent(int font_num);
CTFontRef get_font_ref(int font_num);
double get_leading(int font_num);
double get_xheight(int font_num);
double get_operator_height(int font_num);
void init_fonts(void);
int isdenominator(struct atom *p);
void prep_display(void);
void printbuf(char *s, int color);
void run_thread(char *s);
void * run_thread_nib(void *s);
void shipout(struct display *p);
