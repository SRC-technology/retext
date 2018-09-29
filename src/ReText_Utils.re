module List = {
  include List;
  let init = ls => {
    let rec i = (ls, acc) =>
      switch (ls) {
      | [] => acc
      | [_last] => acc
      | [el, ...els] => i(els, [el, ...acc])
      };
    i(ls, []);
  };

  let last = (ls, el) =>
    List.length(ls) == 0 ? el : List.nth(ls, List.length(ls) - 1);
};
