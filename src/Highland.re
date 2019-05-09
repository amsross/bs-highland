type t('e, 'a);

[@bs.module "highland"] external of_: 'a => t('e, 'a) = "of";
[@bs.module] external on_: (string, 'a) => t('e, 'a) = "highland";
[@bs.module]
external fromStreams: array(t('e, 'a)) => t('e, t('e, 'a)) = "highland";
[@bs.module "highland"] external fromError: 'a => t('e, 'a) = "fromError";

[@bs.send] external take: (t('e, 'a), int) => t('e, 'a) = "take";

[@bs.send]
external flatMap: (t('e, 'a), 'a => t('e, 'b)) => t('e, 'b) = "flatMap";
[@bs.send] external map: (t('e, 'a), 'a => 'b) => t('e, 'b) = "map";
[@bs.send] external tap: (t('e, 'a), 'a => unit) => t('e, 'a) = "tap";

[@bs.send] external merge: t('e, t('e, 'a)) => t('e, 'a) = "merge";

[@bs.send] external errors: (t('e, 'a), 'e => unit) => t('e, 'a) = "errors";
[@bs.send] external each: (t('e, 'a), 'a => unit) => t('e, 'a) = "each";
[@bs.send] external done_: (t('e, 'a), unit => unit) => t('e, 'a) = "done";
