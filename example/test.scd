(
Server.default.options.inDevice_("Built-in Microph");
Server.default.options.outDevice_("Built-in Output");
s.options.sampleRate = 48000;
s.options.blockSize = 64;
s.options.memSize = 1024 * 1024;
s.boot
)

(
Server.default = s = Server("remote", NetAddr("127.0.0.1", 57110));
// s.options.maxLogins = 4; // should match the settings on the Bela
s.initTree;
s.startAliveThread;
)

s.options.asOptionsString

s.reboot

("xattr -d -r com.apple.quarantine"+Platform.userExtensionDir.quote++"/sc-julia/").runInTerminal

(
~synth = {
    JuliaUGen.ar(SinOsc.ar(481), DC.ar(0.1));
}.play
)

~synth.free

s.quit

