open BsBastet;

type data('a);
type t('e, 'a);

external data: 'a => data('a) = "%identity";

type push('e, 'a) = (Js.Nullable.t('e), Js.Nullable.t(data('a))) => unit;
type next('e, 'a) = Js.Nullable.t(t('e, 'a)) => unit;

let __push: (push('e, 'a), result(data('a), 'e)) => unit =
  push =>
    fun
    | Ok(value) => push(Js.Nullable.null, Js.Nullable.return(value))
    | Error(err) => push(Js.Nullable.return(err), Js.Nullable.null);

[@bs.module "highland"] [@bs.val] external nil: data('a) = "nil";
[@bs.module]
external generator: ((push('e, 'a), next('e, 'a)) => unit) => t('e, 'a) =
  "highland";

let generator = callback =>
  generator((push, next) => callback(__push(push), next));

[@bs.module]
external fromPromise: Js.Promise.t('a) => t('e, 'a) = "highland";
[@bs.module] external fromArray: array('a) => t('e, 'a) = "highland";
[@bs.module] external fromEmitter: (string, 'v) => t('e, 'a) = "highland";
[@bs.module "highland"] external fromValue: 'a => t('e, 'a) = "of";
[@bs.module "highland"] external fromError: 'e => t('e, 'a) = "fromError";
[@bs.module "highland"] external empty: unit => t('e, _) = "empty";

[@bs.send] external take: (t('e, 'a), int) => t('e, 'a) = "take";
[@bs.send] external tap: (t('e, 'a), 'a => unit) => t('e, 'a) = "tap";
[@bs.send] external map: (t('e, 'a), 'a => 'b) => t('e, 'b) = "map";
/* the incoming function may need to have been manually curried */
[@bs.send] external ap: (t('e, 'a => 'b), t('e, 'a)) => t('e, 'b) = "ap";
[@bs.send]
external flatMap: (t('e, 'a), 'a => t('e, 'b)) => t('e, 'b) = "flatMap";
[@bs.send] external filter: (t('e, 'a), 'a => bool) => t('e, 'a) = "filter";

[@bs.send] external alt: (t('e, 'a), t('e, 'a)) => t('e, 'a) = "alt";

[@bs.send]
external through: (t('e, 'a), t('e, 'a) => t('e, 'b)) => t('e, 'b) =
  "through";
[@bs.send] external collect: t('e, 'a) => t('e, array('a)) = "collect";
[@bs.send]
external ratelimit: (t('e, 'a), int, int) => t('e, 'a) = "ratelimit";
[@bs.send] external append: (t('e, 'a), t('e, 'a)) => t('e, 'a) = "append";
[@bs.send] external concat: (t('e, 'a), t('e, 'a)) => t('e, 'a) = "concat";
[@bs.send] external merge: t('e, t('e, 'a)) => t('e, 'a) = "merge";
[@bs.send] external sequence: t('e, t('e, 'a)) => t('e, 'a) = "sequence";
[@bs.send]
external scan1: (t('e, 'a), ('a, 'b) => 'c) => t('e, 'c) = "scan1";

[@bs.send]
external consume:
  (
    t('e, 'a),
    (Js.Nullable.t('e), 'a, push('e, 'b), next('e, 'b)) => unit
  ) =>
  t('e, 'b) =
  "consume";

let consume = (stream, callback) =>
  consume(stream, (err, x, push, next) =>
    callback(err, data(x), __push(push), next)
  );

[@bs.send]
external errors: (t('e, 'a), ('e, push('d, 'a)) => unit) => t('d, 'a) =
  "errors";

let errors = (stream, callback) =>
  errors(stream, (err, push) => callback(err, __push(push)));

[@bs.send] external each: (t('e, 'a), 'a => unit) => t('e, 'a) = "each";
[@bs.send] external done_: (t('e, 'a), unit => unit) => unit = "done";
[@bs.send]
external toCallback: (t('e, 'a), (Js.Nullable.t('e), 'a) => unit) => unit =
  "toCallback";

open Interface;

module type MAGMA' =
  (Err: TYPE, Data: TYPE) => MAGMA with type t = t(Err.t, Data.t);

module Magma: MAGMA' =
  (Err: TYPE, Data: TYPE) => {
    type nonrec t = t(Err.t, Data.t);
    let append = concat;
  };

module type FUNCTOR' =
  (Err: TYPE) => FUNCTOR with type t('a) = t(Err.t, 'a);

module Functor: FUNCTOR' =
  (Err: TYPE) => {
    type nonrec t('a) = t(Err.t, 'a);
    let map = (f, a) => map(a, f);
  };

module type APPLY' = (Err: TYPE) => APPLY with type t('a) = t(Err.t, 'a);

module Apply: APPLY' =
  (Err: TYPE) => {
    include Functor(Err);
    let apply = ap;
  };

module type APPLICATIVE' =
  (Err: TYPE) => APPLICATIVE with type t('a) = t(Err.t, 'a);

module Applicative: APPLICATIVE' =
  (Err: TYPE) => {
    include Apply(Err);
    let pure = fromValue;
  };

module type MONAD' = (Err: TYPE) => MONAD with type t('a) = t(Err.t, 'a);

module Monad: MONAD' =
  (Err: TYPE) => {
    include Applicative(Err);
    let flat_map = flatMap;
  };

module type ALT' = (Err: TYPE) => ALT with type t('a) = t(Err.t, 'a);

module Alt: ALT' =
  (Err: TYPE) => {
    include Functor(Err);
    let alt = alt;
  };

module type SEMIGROUP' =
  (Err: TYPE, Data: TYPE) => SEMIGROUP with type t = t(Err.t, Data.t);

module SemiGroup: SEMIGROUP' =
  (Err: TYPE, Data: TYPE) => {
    include Magma(Err, Data);
  };

module type MONOID' =
  (Err: TYPE, Data: TYPE) => MONOID with type t = t(Err.t, Data.t);

module Monoid: MONOID' =
  (Err: TYPE, Data: TYPE) => {
    include SemiGroup(Err, Data);
    let empty = empty();
  };

module InfixM = (Err: TYPE, Data: TYPE) => {
  include Infix.Magma((Magma(Err, Data)));
  include Infix.Monad((Monad(Err)));
  include Infix.Alt((Alt(Err)));
};

module Infix = (Err: TYPE) => {
  include Infix.Monad((Monad(Err)));
  include Infix.Alt((Alt(Err)));
};
