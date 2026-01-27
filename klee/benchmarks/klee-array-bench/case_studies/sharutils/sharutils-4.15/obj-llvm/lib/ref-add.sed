/^# Packages using this file: / {
  s/# Packages using this file://
  ta
  :a
  s/ sharutils / sharutils /
  tb
  s/ $/ sharutils /
  :b
  s/^/# Packages using this file:/
}
