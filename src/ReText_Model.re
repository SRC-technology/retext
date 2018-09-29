type penalty_flag =
  | Flagged
  | Unflagged;

type penalty_cost =
  | Must_break
  | Cost(float);

type penalty = {
  width: float,
  cost: penalty_cost,
  flagged: penalty_flag,
};

type box = {width: float};

type glue = {
  width: float,
  stretchability: float,
  shrinkability: float,
};

type element =
  | Box(box)
  | Glue(glue)
  | Penalty(penalty);

module MeasuredWidth = {
  type t = {
    width: float,
    min: float,
    max: float,
  };

  let empty = {width: 0., min: 0., max: 0.};

  let concat = (a, b) => {
    width: a.width +. b.width,
    min: a.min +. b.min,
    max: a.max +. b.max,
  };

  let t_of_box: box => t = ({width}) => {width, min: width, max: width};

  let t_of_glue = ({width, shrinkability, stretchability}) => {
    width,
    min: width -. shrinkability,
    max: width +. stretchability,
  };

  let measure = els => {
    let rec measure = (es, acc) =>
      switch (es) {
      | [] => acc
      | [Box(b), ...es'] => t_of_box(b) |> concat(acc) |> measure(es')
      | [Glue(g), ...es'] => t_of_glue(g) |> concat(acc) |> measure(es')
      | [_, ...es'] => measure(es', acc)
      };
    measure(els, empty);
  };
};
