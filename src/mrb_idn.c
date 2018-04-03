/*
** mrb_idn.c - IDN class
**
** Copyright (c) Okumura Takahiro 2018
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"

void mrb_init_idna(mrb_state *mrb);

#define DONE mrb_gc_arena_restore(mrb, 0);

void mrb_mruby_idn_gem_init(mrb_state *mrb)
{
  struct RClass *idn, *idnerror;
  idn = mrb_define_module(mrb, "IDN");
  idnerror = mrb_define_class_under(mrb, idn, "IDNError", mrb->eStandardError_class);

  mrb_init_idna(mrb); DONE;
}

void mrb_mruby_idn_gem_final(mrb_state *mrb)
{
}
