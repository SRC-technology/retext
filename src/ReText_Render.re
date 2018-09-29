open ReText_Model;

module S = ReactDOMRe.Style;

let spanStyle = (~bg, ~width) =>
  S.make(
    ~backgroundColor=bg,
    ~width=string_of_float(width) ++ "px",
    ~height="20px",
    ~display="inline-block",
    (),
  );

let renderElement = el =>
  switch (el) {
  | Glue({width}) => <span style={spanStyle(~bg="blue", ~width)} />
  | Box({width}) => <span style={spanStyle(~bg="red", ~width)} />
  | _ => <span />
  };

module C = {
  let component = ReasonReact.statelessComponent("Container");

  let make = _children => {
    ...component,
    render: _self =>
      <div
        style={
          S.make(
            ~backgroundColor="beige",
            ~width="300px",
            ~overflow="scroll",
            (),
          )
        }>
        <div style={S.make(~width="50000", ())}>
          {
            ReText_BestFit.break(ReText_Sample.elements, ~width=300.)
            |> List.map(line =>
                 <div style={S.make(~display="inline-block", ())}>
                   {
                     line
                     |> List.map(renderElement)
                     |> Array.of_list
                     |> ReasonReact.array
                   }
                 </div>
               )
            |> Array.of_list
            |> ReasonReact.array
          }
        </div>
      </div>,
  };
};

ReactDOMRe.renderToElementWithId(<C />, "app");
