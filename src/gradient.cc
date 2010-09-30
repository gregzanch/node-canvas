
//
// gradient.cc
//
// Copyright (c) 2010 LearnBoost <tj@learnboost.com>
//

#include "canvas.h"
#include "gradient.h"

void
Gradient::Initialize(Handle<Object> target) {
  HandleScope scope;
  Local<FunctionTemplate> t = FunctionTemplate::New(Gradient::New);
  t->InstanceTemplate()->SetInternalFieldCount(1);
  t->SetClassName(String::NewSymbol("CanvasGradient"));

  target->Set(String::NewSymbol("CanvasGradient"), t->GetFunction());
}

Handle<Value>
Gradient::New(const Arguments &args) {
  HandleScope scope;

  // Linear
  if (4 == args.Length()) {
    Gradient *grad = new Gradient(
        args[0]->NumberValue()
      , args[1]->NumberValue()
      , args[2]->NumberValue()
      , args[3]->NumberValue());
    grad->Wrap(args.This());
    return args.This();
  }

  // Radial
  if (6 == args.Length()) {
    Gradient *grad = new Gradient(
        args[0]->NumberValue()
      , args[1]->NumberValue()
      , args[2]->NumberValue()
      , args[3]->NumberValue()
      , args[4]->NumberValue()
      , args[5]->NumberValue());
    grad->Wrap(args.This());
    return args.This();
  }
  
  return ThrowException(Exception::TypeError(String::New("invalid arguments")));
}

Gradient::Gradient(double x0, double y0, double x1, double y1):
  _x0(x0), _y0(y0), _x1(x1), _y1(y1) {
  _grad = cairo_pattern_create_linear(x0, y0, x1, y1);
}

Gradient::Gradient(double x0, double y0, double r0, double x1, double y1, double r1):
  _x0(x0), _y0(y0), _x1(x1), _y1(y1), _r0(r0), _r1(r1) {
  _grad = cairo_pattern_create_radial(x0, y0, r0, x1, y1, r1);
}
