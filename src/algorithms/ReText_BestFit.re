open ReText_Model;

let p = Penalty({width: 0., cost: Must_break, flagged: Unflagged});

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

let handle_glue = (glue, lines) =>
  init(lines) @ [last(lines, [p]), [Glue(glue)]];

let handle_box = (box, lines: list(list(element)), desired_width) => {
  let current_element = Box(box);

  let tentative_next_cumulated_width =
    last(lines, [p]) @ [current_element] |> MeasuredWidth.measure;

  let can_break =
    desired_width > tentative_next_cumulated_width.min
    && desired_width < tentative_next_cumulated_width.max;

  can_break ?
    init(lines)
    @ [
      switch (last(last(lines, [p]), p)) {
      | Glue(_) => init(last(lines, [p]))
      | _ => last(lines, [p])
      },
      [current_element],
    ] :
    init(lines) @ [last(lines, [p]) @ [current_element]];
};

let break = (elements, ~width) => {
  let rec break = (elements, lines) =>
    switch (elements) {
    | [] => lines
    | [Box(b), ...els] => break(els, handle_box(b, lines, width))
    | [Glue(g), ...els] => break(els, handle_glue(g, lines))
    | [Penalty(_), ...els] => break(els, lines)
    };
  break(elements, []);
};
