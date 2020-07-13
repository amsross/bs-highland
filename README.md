# bs-highland

Bucklescript/ReasonML bindings for [highlandjs](https://highlandjs.org).


## Installation

```sh
npm install --save @amsross/bs-highland
```

Then add `@amsross/bs-highland` to `bs-dependencies` in your `bsconfig.json`:

```js
{
  ...
  "bs-dependencies": ["@amsross/bs-highland"]
}
```

# Usage

## Generators / Push / Next

Wrap pushed data in `Ok(data(thing))` and errors in `Error(err)`
```
Highland.generator((push, next) => {
  condition ? push(Ok(Highland.data("something"))) : push(Error(err));
  setTimeout(() => next(Js.Nullable.null), 1000);
});
```
