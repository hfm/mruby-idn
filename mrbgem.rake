require "#{MRUBY_ROOT}/lib/mruby/source"

MRuby::Gem::Specification.new('mruby-idn') do |spec|
  spec.license = 'MIT'
  spec.authors = 'Okumura Takahiro'
  spec.summary = 'Libidn2 mruby bindings'
  spec.description = %q{
    mruby bindings for the libidn2 library,
    an implementation of IDNA2008, Punycode and TR46
    defined by the IETF Internationalized Domain Names working group.
  }

  spec.linker.libraries << 'idn2'
  if RUBY_PLATFORM =~ /darwin/i
    spec.cc.flags << "-I/usr/local/include"
    spec.linker.library_paths << "/usr/local/lib"
  end

  spec.add_test_dependency 'mruby-mtest'
  if MRuby::Source::MRUBY_VERSION >= '1.4.0'
    spec.add_dependency 'mruby-pack', core: 'mruby-pack'
  else
    spec.add_dependency 'mruby-pack'
  end
end
