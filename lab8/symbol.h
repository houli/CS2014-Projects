typedef enum {
  false, true
} bool;

typedef struct symbol symbol;

struct symbol {
  union {
    struct {
      symbol * left;
      symbol * right;
    } children;
    unsigned char c;
  } data;
  int frequency;
  bool is_leaf;
};

symbol * symbol_new_char(int frequency, char c);

symbol * symbol_new_children(int frequency, symbol * left, symbol * right);

void symbol_free(symbol * symbol);
