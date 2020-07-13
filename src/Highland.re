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

/* Transforms */

/* append */
[@bs.send] external append: (t('e, 'a), t('e, 'a)) => t('e, 'a) = "append";

/* batch */
[@bs.send] external batch: (t('e, 'a), int) => t('e, array('a)) = "batch";

/* batchWithTimeOrCount */
[@bs.send]
external batchWithTimeOrCount:
  (t('e, 'a), ~ms: int, ~n: int) => t('e, array('a)) =
  "batchWithTimeOrCount";

/* collect */
[@bs.send] external collect: t('e, 'a) => t('e, array('a)) = "collect";

/* compact */
[@bs.send] external compact: t('e, 'a) => t('e, 'a) = "compact";

[@bs.send]
external consume:
  (
    t('e, 'a),
    (Js.Nullable.t('e), 'a, push('e, 'b), next('e, 'b)) => unit
  ) =>
  t('e, 'b) =
  "consume";

/* consume */
let consume = (stream, callback) =>
  consume(stream, (err, x, push, next) =>
    callback(err, data(x), __push(push), next)
  );

/* doto */
[@bs.send] external doto: (t('e, 'a), 'a => unit) => t('e, 'a) = "doto";

/* drop */
[@bs.send] external drop: (t('e, 'a), int) => t('e, 'a) = "drop";

[@bs.send]
external errors: (t('e, 'a), ('e, push('d, 'a)) => unit) => t('d, 'a) =
  "errors";

/* errors */
let errors = (stream, callback) =>
  errors(stream, (err, push) => callback(err, __push(push)));

/* filter */
[@bs.send] external filter: (t('e, 'a), 'a => bool) => t('e, 'a) = "filter";

/* find */
[@bs.send] external find: (t('e, 'a), 'a => bool) => t('e, 'a) = "find";

/* findWhere */
[@bs.send]
external findWhere: (t('e, 'a), Js.t('props)) => t('e, 'a) = "findWhere";

/* group */
[@bs.send]
external group:
  (
    t('e, 'a),
    [@bs.unwrap] [ | `Function('a => string) | `String(string)]
  ) =>
  t('e, 'a) =
  "group";

/* head */
[@bs.send] external head: t('e, 'a) => t('e, 'a) = "head";

/* intersperse. this doesn't seem like it belongs in ReasonML */

/* invoke */
[@bs.send]
external intersperse: (t('e, string), string) => t('e, string) =
  "intersperse";

/* latest */
[@bs.send] external latest: t('e, 'a) => t('e, 'b) = "latest";

/* map */
[@bs.send] external map: (t('e, 'a), 'a => 'b) => t('e, 'b) = "map";

/* nfcall. this doesn't seem like it belongs in ReasonML */

/* pick. this doesn't seem like it belongs in ReasonML */
[@bs.send]
external pick: (t('e, Js.t('a)), array(string)) => t('e, Js.t('b)) =
  "pick";

/* pickBy */
[@bs.send]
external pickBy: (t('e, Js.t('a)), ('key, 'value) => 'b) => t('e, Js.t('b)) =
  "pickBy";
/* pluck */
[@bs.send] external pluck: (t('e, Js.t('a)), string) => t('e, 'b) = "pluck";

/* ratelimit */
[@bs.send]
external ratelimit: (t('e, 'a), int, int) => t('e, 'a) = "ratelimit";

/* reject */
[@bs.send] external reject: (t('e, 'a), 'a => bool) => t('e, 'a) = "reject";

/* scan */
[@bs.send]
external scan: (t('e, 'a), ~memo: 'b, ~iterator: ('a, 'b) => 'b) => t('e, 'b) =
  "scan";

/* scan1 */
[@bs.send]
external scan1: (t('e, 'a), ('a, 'b) => 'b) => t('e, 'b) = "scan1";

/* slice */
[@bs.send]
external slice: (t('e, 'a), ~start: int, ~stop: int) => t('e, 'a) = "slice";

/* sort */
[@bs.send] external sort: t('e, 'a) => t('e, 'a) = "sort";

/* sortBy */
[@bs.send] external sortBy: (t('e, 'a), 'a => int) => t('e, 'a) = "sortBy";

/* split */
[@bs.send] external split: t('e, 'a) => t('e, 'a) = "split";

/* splitBy */
[@bs.send]
external splitBy:
  (t('e, 'a), [@bs.unwrap] [ | `String(string) | `Regex(Js.Re.t)]) =>
  t('e, 'a) =
  "splitBy";

/* stopOnError */
[@bs.send]
external stopOnError: (t('e, 'a), 'e => unit) => t('e, 'a) = "stopOnError";

/* take */
[@bs.send] external take: (t('e, 'a), int) => t('e, 'a) = "take";

/* tap */
[@bs.send] external tap: (t('e, 'a), 'a => unit) => t('e, 'a) = "tap";

/* throttle */
[@bs.send] external throttle: (t('e, 'a), int) => t('e, 'a) = "throttle";

/* transduce */
/* [@bs.send] external transduce: (t('e, 'a), transducer) => t('e, 'a) = "transduce"; */

/* uniq */
[@bs.send] external uniq: t('e, 'a) => t('e, 'a) = "uniq";

/* uniqBy */
[@bs.send] external uniqBy: (t('e, 'a), 'a => bool) => t('e, 'a) = "uniqBy";

/* where */
[@bs.send] external where: (t('e, 'a), Js.t('obj)) => t('e, 'a) = "where";

/* Higher-Order Streams */

/* alt */
[@bs.send] external alt: (t('e, 'a), t('e, 'a)) => t('e, 'a) = "alt";

/* ap. the incoming function may need to have been manually curried */
[@bs.send] external ap: (t('e, 'a => 'b), t('e, 'a)) => t('e, 'b) = "ap";

/* concat */
[@bs.send] external concat: (t('e, 'a), t('e, 'a)) => t('e, 'a) = "concat";

/* flatFilter */
external flatFilter: (t('e, 'a), 'a => t('e, bool)) => t('e, 'a) =
  "flatFilter";

/* flatMap */
[@bs.send]
external flatMap: (t('e, 'a), 'a => t('e, 'b)) => t('e, 'b) = "flatMap";

/* flatten */
[@bs.send]
external flatten:
  (
  [@bs.unwrap]
  [ | `Stream(t('e, t('e, 'a))) | `Array(t('e, array('a)))]
  ) =>
  t('e, 'a) =
  "flatten";

/* fork */
[@bs.send] external fork: t('e, 'a) => t('e, 'a) = "fork";

/* merge */
[@bs.send] external merge: t('e, t('e, 'a)) => t('e, 'a) = "merge";

/* mergeWithLimit */
[@bs.send]
external mergeWithLimit: (t('e, t('e, 'a)), int) => t('e, 'a) =
  "mergeWithLimit";

/* observe */
[@bs.send] external observe: t('e, 'a) => t('e, 'a) = "observe";

/* otherwise */
[@bs.send]
external otherwise: (t('e, 'a), t('e, 'a)) => t('e, 'a) = "otherwise";

/* parallel */
[@bs.send] external parallel: (t('e, 'a), int) => t('e, 'a) = "parallel";

/* pipeline. this doesn't seem like it belongs in ReasonML */

/* sequence */
[@bs.send]
external sequence:
  (
  [@bs.unwrap]
  [ | `Stream(t('e, t('e, 'a))) | `Array(t('e, array('a)))]
  ) =>
  t('e, 'a) =
  "sequence";

/* series */
[@bs.send]
external series:
  (
  [@bs.unwrap]
  [ | `Stream(t('e, t('e, 'a))) | `Array(t('e, array('a)))]
  ) =>
  t('e, 'a) =
  "series";

/* through */
[@bs.send]
external through: (t('e, 'a), t('e, 'a) => t('e, 'b)) => t('e, 'b) =
  "through";

/* zip */
[@bs.send]
external zip:
  (t('e, 'a), [@bs.unwrap] [ | `Stream(t('e, 'b)) | `Array(array('b))]) =>
  t('e, ('a, 'b)) =
  "zip";

/* zipAll */
[@bs.send]
external zipAll: t('e, t('e, 'a)) => t('e, array('a)) = "zipAll";

/* Consumption */

/* apply. this doesn't seem like it belongs in ReasonML */

/* done */
[@bs.send] external done_: (t('e, 'a), unit => unit) => unit = "done";

/* each */
[@bs.send] external each: (t('e, 'a), 'a => unit) => t('e, 'a) = "each";

/* pipe */
[@bs.send]
external pipe:
  (t('e, 'a), 'node_stream, ~options: Js.t('options)=?, unit) => t('e, 'a) =
  "pipe";

/* pull */
[@bs.send] external pull: (t('e, 'a), ('e, 'a) => unit) => unit = "pull";

/* toArray */
[@bs.send] external toArray: (t('e, 'a), array('a)) => unit = "toArray";

/* toCallback */
[@bs.send]
external toCallback: (t('e, 'a), (Js.Nullable.t('e), 'a) => unit) => unit =
  "toCallback";

/* toNodeStream */
[@bs.send] external toNodeStream: t('e, 'a) => 'node_stream = "toNodeStream";

/* toPromise */
[@bs.send] external toPromise: t('e, 'a) => Js.Promise.t('a) = "toPromise";

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
