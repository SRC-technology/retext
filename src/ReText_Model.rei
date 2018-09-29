/**

  {1:top Core Types}

  ReText works in accordance to the core abstractions defined in Knuth's paper {e Breaking Lines into Paragraphs}.

  These are outlined below:

*/;

/**
  The {!penalty_flat} type indicates whether a particular penalty is marked to be ...
  */
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

module MeasuredWidth: {
  type t = {
    width: float,
    min: float,
    max: float,
  };

  let measure: list(element) => t;
};
