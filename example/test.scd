(
Server.default.options.inDevice_("Built-in Microph");
Server.default.options.outDevice_("Built-in Output");
s.options.sampleRate = 48000;
s.options.blockSize = 64;
s.options.memSize = 1024 * 1024;
s.boot
)

s.reboot

("xattr -d -r com.apple.quarantine"+Platform.userExtensionDir.quote++"/sc-julia/").runInTerminal

(
~synth = {
    JuliaUGen.ar(SinOsc.ar, DC.ar(0.1));
}.play
)

~synth.free

s.quit