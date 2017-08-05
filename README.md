# Kaleidoscope-LED-Wavepool

![status][st:experimental] [![Build Status][travis:image]][travis:status]

 [travis:image]: https://travis-ci.org/keyboardio/Kaleidoscope-LED-Wavepool.svg?branch=master
 [travis:status]: https://travis-ci.org/keyboardio/Kaleidoscope-LED-Wavepool

 [st:stable]: https://img.shields.io/badge/stable-✔-black.svg?style=flat&colorA=44cc11&colorB=494e52
 [st:broken]: https://img.shields.io/badge/broken-X-black.svg?style=flat&colorA=e05d44&colorB=494e52
 [st:experimental]: https://img.shields.io/badge/experimental----black.svg?style=flat&colorA=dfb317&colorB=494e52

The `WavepoolEffect` plugin provides an interesting new typing experience: the
LEDs light up as you tap keys and play one of the selected effects: a haunting
trail of ghostly white lights, or a blazing trail of fire.

## Using the plugin

To use the plugin, one needs to include the header and select the effect.

```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-LED-Wavepool.h>

void setup (){
  Kaleidoscope.use(&WavepoolEffect);

  Kaleidoscope.setup();

  WavepoolEffect.variant = WAVEPOOL(Haunt, (CRGB(0, 128, 0)));
  WavepoolEffect.activate();
}
```

It is recommended to place the activation of the plugin (the `USE_PLUGINS` call)
as early as possible, so the plugin can catch all relevant key presses. The
configuration can happen at any time and should use the `WAVEPOOL` macro to do so.

## Plugin methods

The plugin provides the `WavepoolEffect` object, which has the following
properties:

### `.variant`

> Set the effect to use with the plugin. See below for a list.
>
> It is recommended to use the `WAVEPOOL` macro to declare the effect itself.

### `.stepLength`

> The length - in milliseconds - of each step of the animation. An animation
> lasts 256 steps.
>
> Defaults to 50.

## Plugin helpers

### `WAVEPOOL(effect, params)`

> Returns an effect, to be used to assign a value the `.variant` property of the
> `WavepoolEffect` object. Any arguments given to the macro are passed on
> to the effect. If the effect takes no arguments, use an empty `params` list.

## Plugin effects

The plugin provides the following effects:

### `Haunt([color])`

> A ghostly haunt effect, that trails the key taps with a ghostly white color
> (or any other color, if specified). Use the `CRGB(r,g,b)` macro to specify the
> color, if you want something else than the ghostly white.

### `BlazingTrail()`

> A blazing trail of fire will follow our fingers!

## Dependencies

* [Kaleidoscope-LEDControl](https://github.com/keyboardio/Kaleidoscope-LEDControl)

## Further reading

Starting from the [example][plugin:example] is the recommended way of getting
started with the plugin.

 [plugin:example]: https://github.com/keyboardio/Kaleidoscope-LED-Wavepool/blob/master/examples/LED-Wavepool/LED-Wavepool.ino
