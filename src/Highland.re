type t('e, 'a);
type nil;

type push('e, 'a) = (Js.Nullable.t('e), Js.Nullable.t('a)) => unit;
type next('e, 'a) = Js.Nullable.t(t('e, 'a)) => unit;

[@bs.module "highland"] [@bs.val] external nil: nil = "nil";

/* construction */
[@bs.module] external on_: (string, 'a) => t('e, 'a) = "highland";
[@bs.module] external fromArray: array('a) => t('e, 'a) = "highland";
[@bs.module]
external fromStreams: array(t('e, 'a)) => t('e, t('e, 'a)) = "highland";
[@bs.module]
external fromPromise: Js.Promise.t('a) => t('e, 'a) = "highland";
[@bs.module]
external fromGenerator: ((push('e, 'a), next('e, 'a)) => unit) => t('e, 'a) =
  "highland";
[@bs.module "highland"] external fromValue: 'a => t('e, 'a) = "of";
[@bs.module "highland"] external fromError: 'a => t('e, 'a) = "fromError";
[@bs.module "highland"] external empty: unit => t('e, _) = "empty";

/* transforms */
[@bs.send] external append: (t('e, 'a), t('e, 'a)) => t('e, 'a) = "append";
[@bs.send] external batch: (t('e, 'a), int) => t('e, 'a) = "batch";
[@bs.send]
external batchWithTimeOrCount: (t('e, 'a), int, int) => t('e, 'a) =
  "batchWithTimeOrCount";
[@bs.send] external collect: t('e, 'a) => t('e, array('a)) = "collect";
[@bs.send] external compact: t('e, 'a) => t('e, 'a) = "compact";
[@bs.send]
external consume:
  (t('e, 'a), ('e, 'a, push('e, 'a), next('e, 'a)) => unit) => t('e, 'a) =
  "consume";
[@bs.send] external debounce: (t('e, 'a), int) => t('e, 'a) = "debounce";
[@bs.send] external doto: (t('e, 'a), 'a => unit) => t('e, 'a) = "doto";
[@bs.send] external drop: (t('e, 'a), int) => t('e, 'a) = "drop";
[@bs.send]
external errors: (t('e, 'a), 'e, push('e, 'a) => unit) => t('e, 'a) =
  "errors";
[@bs.send] external filter: (t('e, 'a), 'a => bool) => t('e, 'a) = "filter";
[@bs.send] external find: (t('e, 'a), 'a => bool) => t('e, 'a) = "find";
[@bs.send]
external findWhere: (t('e, 'a), Js.t({..})) => t('e, 'a) = "findWhere";
[@bs.send]
external group: (t('e, 'a), 'a => 'b) => t('e, Js.t(array('a))) = "group";
[@bs.send] external head: t('e, 'a) => t('e, 'a) = "head";
[@bs.send]
external intersperse: (t('e, string), string) => t('e, string) =
  "intersperse";
/* invoke */
[@bs.send] external last: t('e, 'a) => t('e, 'a) = "last";
[@bs.send] external latest: t('e, 'a) => t('e, 'a) = "latest";
[@bs.send] external map: (t('e, 'a), 'a => 'b) => t('e, 'b) = "map";
/* nfcall */
[@bs.send] external pick: (t('e, 'a), array(string)) => t('e, 'b) = "pick";
[@bs.send]
external pickBy: (t('e, 'a), (string, 'a) => bool) => t('e, 'b) = "pickBy";
[@bs.send] external pluck: (t('e, 'a), string) => t('e, 'b) = "pluck";
[@bs.send] external ratelimit: (t('e, 'a), int) => t('e, 'b) = "ratelimit";
[@bs.send]
external reduce: (t('e, 'a), 'b, ('a, 'b) => 'b) => t('e, 'b) = "reduce";
[@bs.send]
external reduce1: (t('e, 'a), ('a, 'b) => 'b) => t('e, 'b) = "reduce1";
[@bs.send] external reject: (t('e, 'a), 'a => bool) => t('e, 'a) = "reject";
[@bs.send]
external scan: (t('e, 'a), 'b, ('a, 'b) => 'b) => t('e, 'b) = "scan";
[@bs.send]
external scan1: (t('e, 'a), ('a, 'b) => 'b) => t('e, 'b) = "scan1";
[@bs.send] external slice: (t('e, 'a), int, int) => t('e, 'a) = "slice";
[@bs.send] external sort: t('e, 'a) => t('e, 'a) = "sort";
[@bs.send]
external sortBy: (t('e, 'a), ('a, 'a) => int) => t('e, 'a) = "sortBy";
[@bs.send] external split: t('e, 'a) => t('e, 'a) = "split";
[@bs.send]
external splitBy: (t('e, string), string) => t('e, string) = "splitBy";
[@bs.send]
external stopOnError: (t('e, 'a), 'e => unit) => t('e, 'a) = "stopOnError";
[@bs.send] external take: (t('e, 'a), int) => t('e, 'a) = "take";
[@bs.send] external tap: (t('e, 'a), 'a => unit) => t('e, 'a) = "tap";
[@bs.send] external throttle: (t('e, 'a), int) => t('e, 'a) = "throttle";
/* transduce */
[@bs.send] external uniq: t('e, 'a) => t('e, 'a) = "uniq";
[@bs.send]
external uniqBy: (t('e, 'a), ('a, 'a) => bool) => t('e, 'a) = "uniqBy";
[@bs.send] external where: (t('e, 'a), Js.t({..})) => t('e, 'a) = "where";

/* higher-order streams */
[@bs.send] external concat: (t('e, 'a), t('e, 'a)) => t('e, 'a) = "concat";
[@bs.send]
external flatFilter: (t('e, 'a), 'a => t('e, bool)) => t('e, 'a) =
  "flatFilter";
[@bs.send]
external flatMap: (t('e, 'a), 'a => t('e, 'b)) => t('e, 'b) = "flatMap";
[@bs.send] external flattenArray: t('e, array('a)) => t('e, 'a) = "flatten";
[@bs.send]
external flattenStreams: t('e, t('e, 'a)) => t('e, 'a) = "flatten";
[@bs.send] external fork: t('e, 'a) => t('e, 'a) = "fork";
[@bs.send] external merge: t('e, t('e, 'a)) => t('e, 'a) = "merge";
[@bs.send]
external mergeWithLimit: (t('e, t('e, 'a)), int) => t('e, 'a) =
  "mergeWithLimit";
[@bs.send] external observe: t('e, 'a) => t('e, 'a) = "observe";
[@bs.send] external otherwise: (t('e, 'a), 'a) => t('e, 'a) = "otherwise";
[@bs.send]
external parallel: (t('e, t('e, 'a)), int) => t('e, 'a) = "parallel";
/* pipeline */
[@bs.send]
external sequenceArray: t('e, array('a)) => t('e, 'a) = "sequence";
[@bs.send]
external sequenceStreams: t('e, t('e, 'a)) => t('e, 'a) = "sequence";
[@bs.send] external seriesArray: t('e, array('a)) => t('e, 'a) = "series";
[@bs.send] external seriesStreams: t('e, t('e, 'a)) => t('e, 'a) = "series";
[@bs.send]
external through: (t('e, 'a), t('e, 'a) => t('e, 'b)) => t('e, 'b) =
  "through";
[@bs.send]
external zip: (t('e, 'a), t('e, 'a)) => t('e, array('a)) = "zip";
[@bs.send]
external zipAll: (t('e, 'a), array(t('e, 'a))) => t('e, array('a)) =
  "zipAll";
[@bs.send]
external zipAll0: array(t('e, 'a)) => t('e, array('a)) = "zipAll0";

/* consumption */
/* apply */
[@bs.send] external done_: (t('e, 'a), unit => unit) => t('e, 'a) = "done";
[@bs.send] external each: (t('e, 'a), 'a => unit) => t('e, 'a) = "each";
/* pipe */
[@bs.send]
external toArray: (t('e, 'a), array('a) => unit) => t('e, 'a) = "toArray";
[@bs.send]
external toCallback: (t('e, 'a), (Js.Nullable.t('e), 'a) => unit) => unit =
  "toCallback";
/* toNodeStream */
/* toPromise */

/* utils */
/* fromError */
[@bs.module "highland"] external isNil: 'a => bool = "isNil";
[@bs.module "highland"] external isStream: 'a => bool = "isStream";
/* log */
/* nil */
/* of */
/* streamifyAll */
/* wrapCallback */

/* objects */
[@bs.module "highland"]
external extend: (Js.t({..}), Js.t({..})) => Js.t({..}) = "extend";
[@bs.module "highland"] external get: (string, Js.t({..})) => 'a = "get";
[@bs.module "highland"] external keys: Js.t({..}) => t('e, string) = "keys";
[@bs.module "highland"]
external pairs: Js.t({..}) => t('e, (string, 'a)) = "pairs";
[@bs.module "highland"]
external set: (string, 'a, Js.t({..})) => Js.t({..}) = "set";
[@bs.module "highland"] external values: Js.t({..}) => t('e, 'a) = "values";

/* functions */
[@bs.module "highland"] [@bs.variadic]
external compose: array('a => 'b) => (. 'a) => 'b = "compose";
/* compose */
/* curry */
/* flip */
/* ncurry */
/* partial */
/* seq */
