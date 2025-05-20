import re

# Example input data
input_data = """
00:13.944: you
00:14.168: know
00:14.316: what
00:14.553: this
00:14.889: is
00:15.895: It's
00:16.628: a
00:16.817: celebration
00:17.573: bitches
00:18.814: grab
00:19.525: a
00:19.709: drink
00:20.021: grab
00:20.285: a
00:20.469: glass
00:21.695: after
00:22.673: that
00:22.869: I
00:23.029: grab
00:23.245: your
00:23.485: ass
00:23.809: why
00:24.029: you
00:24.189: acting
00:24.645: all
00:25.417: shy
00:25.700: and
00:26.116: all
00:26.937: why
00:27.200: is
00:27.637: y'all
00:28.453: lying
00:29.009: for
00:29.509: I
00:29.789: never
00:30.061: did
00:30.296: this
00:30.553: before
00:31.545: stop
00:32.305: that
00:32.656: What
00:32.917: you
00:33.089: want
00:33.249: some
00:33.493: patron
00:34.609: I
00:35.037: got
00:35.236: that
00:35.577: I
00:35.781: mean
00:35.957: I
00:36.157: promise
00:36.477: y'all
00:37.189: you
00:37.613: fine
00:37.889: and
00:38.105: all
00:38.625: and
00:38.900: your
00:39.161: girlfriend
00:39.584: she
00:39.909: kinda
00:40.289: raw
00:40.809: but
00:41.089: she
00:41.361: not
00:41.681: like
00:42.029: you
00:43.195: No
00:44.049: she
00:44.321: not
00:44.669: like
00:45.001: you
00:46.215: Right
00:47.157: now
00:47.413: I
00:47.609: need
00:47.853: you
00:48.272: to
00:48.557: mute
00:49.005: all
00:49.305: the
00:49.545: monologue
00:50.557: All
00:50.806: that
00:51.105: talking
00:51.477: is
00:51.677: gon
00:51.973: give
00:52.169: me
00:52.329: a
00:52.516: Tylenol
00:53.441: You
00:53.797: put
00:54.025: a
00:54.181: nigga
00:54.504: to
00:54.717: sleep
00:55.205: I'm
00:55.489: tired
00:55.677: of
00:55.876: y'all
00:56.313: Right
00:56.569: now
00:56.757: that
00:56.957: Louis
00:57.305: Vuitton
00:57.857: dine
00:58.253: is
00:58.504: signing
00:58.945: off
00:59.493: But
01:00.033: I
01:00.289: just
01:00.477: thought
01:00.677: you
01:00.876: should
01:01.105: know
01:01.513: We
01:01.797: hit
01:01.997: the
01:02.169: liquor
01:02.533: store
01:03.057: got
01:03.260: some
01:03.409: Christmas
01:04.324: and
01:04.828: we
01:05.045: about
01:05.341: to
01:05.549: let
01:05.737: it
01:05.909: flow
01:06.735: oh
01:07.977: oh
01:09.057: oh
01:10.149: oh
01:10.993: oh
01:11.865: Had
01:12.229: some
01:12.417: problems
01:12.833: before
01:13.365: but
01:13.669: see
01:13.884: we
01:14.125: let
01:14.336: them
01:14.537: go
01:14.961: Got
01:15.257: an
01:15.429: ounce
01:15.657: of
01:15.801: that
01:15.977: draw
01:16.505: and
01:16.749: we
01:16.965: about
01:17.261: to
01:17.497: let
01:17.669: it
01:17.857: flow
01:18.485: Yeah
01:25.384: you
01:25.685: know
01:25.869: what
01:26.113: this
01:26.420: is
01:27.435: It's
"""

# Lists to hold delays and characters
delays = []
characters = []

# Process each line
for line in input_data.strip().split('\n'):
    parts = line.split(': ')
    if len(parts) == 2:
        time, word = parts
        word += " "
        # Convert time to milliseconds
        time_parts = time.split('.')
        seconds = sum(float(part) * (60 ** i) for i, part in enumerate(reversed(time_parts[0].split(':'))))
        milliseconds = int(seconds * 1000 + float(f"0.{time_parts[1]}") * 1000)
        
        # Add delay for first character, then zeros for the rest
        delays.append(milliseconds)
        characters.append(word[0])
        for char in word[1:]:
            delays.append(0)
            characters.append(char)

# Convert lists to C-style arrays for output
delays_str = ', '.join(map(str, delays))
chars_str = ', '.join([f"'{char}'" for char in characters])

# Output the arrays
print(f"int delays[] = {{{delays_str}}};")
print(f"char characters[] = {{{chars_str}}};")