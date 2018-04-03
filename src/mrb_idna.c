/*
** mrb_idna.c - IDNA class
**
** Copyright (c) Okumura Takahiro 2018
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/string.h"
#include "mruby/value.h"
#include <idn2.h>

#ifndef IDNA_ACE_PREFIX
#define IDNA_ACE_PREFIX "xn--"
#endif

#define E_IDNA_ERROR (mrb_exc_get(mrb, "IdnaError"))

mrb_value
mrb_idna_to_ascii(mrb_state *mrb, mrb_value self)
{
  mrb_value str;
  mrb_int flags;
  mrb_value retv;
  char *p;
  int rc;

  flags = 0x0000;
  mrb_get_args(mrb, "S|i", &str, &flags);

  rc = idn2_to_ascii_8z(RSTRING_PTR(str), &p, (int)flags);
  /* IDNA2003 - compatible */
  if (rc == IDN2_DISALLOWED) {
    rc = idn2_to_ascii_8z(RSTRING_PTR(str), &p, IDN2_TRANSITIONAL);
  }
  if (rc != IDN2_OK) {
    mrb_raisef(mrb, E_IDNA_ERROR, "%s (%d)", idn2_strerror(rc), rc);
  }

  retv = mrb_str_new_cstr(mrb, p);
  return retv;
}

mrb_value
mrb_idna_to_unicode(mrb_state *mrb, mrb_value self)
{
  mrb_value str;
  mrb_int flags;
  mrb_value retv;
  char *p;
  int rc;

  flags = 0x0000;
  mrb_get_args(mrb, "S|i", &str, &flags);

  rc = idn2_to_unicode_8z8z(RSTRING_PTR(str), &p, (int)flags);
  /* IDNA2003 - compatible */
  if (rc == IDN2_DISALLOWED) {
    rc = idn2_to_ascii_8z(RSTRING_PTR(str), &p, IDN2_TRANSITIONAL);
  }
  if (rc != IDN2_OK) {
    mrb_raisef(mrb, E_IDNA_ERROR, "%s (%d)", idn2_strerror(rc), rc);
  }

  retv = mrb_str_new_cstr(mrb, p);
  return retv;
}

void mrb_init_idna(mrb_state *mrb)
{
  struct RClass *idn, *idnerror;
  struct RClass *idna, *idnaerror;

  idn = mrb_define_module(mrb, "IDN");
  idnerror = mrb_define_class_under(mrb, idn, "IDNError", mrb->eStandardError_class);

  idna = mrb_define_module_under(mrb, idn, "Idna");
  idnaerror= mrb_define_class_under(mrb, idna, "IdnaError", idnerror);

  mrb_define_const(mrb, idna, "ACE_PREFIX", mrb_str_new_cstr(mrb, IDNA_ACE_PREFIX));

  mrb_define_const(mrb, idna, "NFC_INPUT", mrb_fixnum_value(IDN2_NFC_INPUT));
  mrb_define_const(mrb, idna, "ALABEL_ROUNDTRIP", mrb_fixnum_value(IDN2_ALABEL_ROUNDTRIP));
  mrb_define_const(mrb, idna, "TRANSITIONAL", mrb_fixnum_value(IDN2_TRANSITIONAL));
  mrb_define_const(mrb, idna, "NONTRANSITIONAL", mrb_fixnum_value(IDN2_NONTRANSITIONAL));
  mrb_define_const(mrb, idna, "ALLOW_UNASSIGNED", mrb_fixnum_value(IDN2_ALLOW_UNASSIGNED));
  mrb_define_const(mrb, idna, "USE_STD3_ASCII_RULES", mrb_fixnum_value(IDN2_USE_STD3_ASCII_RULES));

  mrb_define_singleton_method(mrb, (struct RObject *)idna, "toASCII", mrb_idna_to_ascii, MRB_ARGS_ARG(1, 1));
  mrb_define_singleton_method(mrb, (struct RObject *)idna, "toUnicode", mrb_idna_to_unicode, MRB_ARGS_ARG(1, 1));
}
