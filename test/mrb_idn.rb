##
## IDN Test
##

assert("IDN#hello") do
  t = IDN.new "hello"
  assert_equal("hello", t.hello)
end

assert("IDN#bye") do
  t = IDN.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("IDN.hi") do
  assert_equal("hi!!", IDN.hi)
end
