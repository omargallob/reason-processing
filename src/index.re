open Reprocessing;

type fruit = {
  px: float,
  py: float,
  vx: float,
  vy: float,
  image: Reprocessing.imageT,
};

type state = {fruits: list(fruit)};

let setup = env => {
  Env.size(~width=600, ~height=600, env);
  let apple =
    Draw.loadImage(
      ~filename="assets/fruit-ninja-assets/apple.png",
      ~isPixel=true,
      env,
    );
  let banana =
    Draw.loadImage(
      ~filename="assets/fruit-ninja-assets/banana.png",
      ~isPixel=true,
      env,
    );
  let bomb =
    Draw.loadImage(
      ~filename="assets/fruit-ninja-assets/bomb.png",
      ~isPixel=true,
      env,
    );
  let fruits = [
    {px: 20.0, py: 0.0, vx: 0.0, vy: 0.0, image: apple},
    {px: 100.0, py: 0.0, vx: 0.0, vy: 0.0, image: banana},
    {px: 50.0, py: 0.0, vx: 0.0, vy: 0.0, image: bomb},
  ];
  ();
  /* let fruit = {px: 0.0, py: 0.0, vx: 0.0, vy: 0.0, image}; */
  {fruits: fruits};
};

let position = py => py <= 120.0 ? py +. 0.5 : py -. 0.5;
let draw = (state, env) => {
  Draw.background(Utils.color(~r=255, ~g=80, ~b=255, ~a=255), env);
  Draw.fill(Utils.color(~r=41, ~g=166, ~b=244, ~a=255), env);

  /* print_endline(string_of_float(sin(Unix.time() ) *. 150.0)) */
  /* print_endline(string_of_int()); */
  /*
   Draw.image(
     state.image,
     ~pos=(int_of_float(state.px), int_of_float(state.py)),
     ~width=300,
     ~height=300,
     env,
   ); */

  let listOfFruits =
    List.map(
      fruit => {
        ...fruit,
        px: fruit.px,
        py: position(fruit.py),
        vx: 100.0,
        vy: 100.0,
      },
      state.fruits,
    );
  List.iter(
    fruit =>
      Draw.image(
        fruit.image,
        ~pos=(int_of_float(fruit.px), int_of_float(fruit.py)),
        ~width=300,
        ~height=300,
        env,
      ),
    listOfFruits,
  );
  {...state, fruits: listOfFruits};
};

run(~setup, ~draw, ());