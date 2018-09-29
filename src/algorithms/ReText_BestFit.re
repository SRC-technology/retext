open ReText_Utils;
open ReText_Model;

let p = Penalty({width: 0., cost: Must_break, flagged: Unflagged});

let handle_glue = (glue, lines) =>
  List.init(lines) @ [List.last(lines, [p]), [Glue(glue)]];

let handle_box = (box, lines: list(list(element)), desired_width) => {
  let current_element = Box(box);

  let tentative_next_cumulated_width =
    List.last(lines, [p]) @ [current_element] |> MeasuredWidth.measure;

  let can_break =
    desired_width > tentative_next_cumulated_width.min
    && desired_width < tentative_next_cumulated_width.max;

  can_break ?
    List.init(lines)
    @ [
      switch (List.last(List.last(lines, [p]), p)) {
      | Glue(_) => List.init(List.last(lines, [p]))
      | _ => List.last(lines, [p])
      },
      [current_element],
    ] :
    List.init(lines) @ [List.last(lines, [p]) @ [current_element]];
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
