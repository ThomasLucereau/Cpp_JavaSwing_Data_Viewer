<h1>INF224 – Multimedia Project (C++ & Java Swing)</h1>

<p>
This project was developed as part of the <b>INF224 – Object-Oriented Programming</b> course 

It consists of two main parts:
<ul>
  <li>A <b>C++ multimedia server</b> managing photos, videos, and films.</li>
  <li>A <b>Java Swing graphical interface</b> acting as a remote control client.</li>
</ul>
</p>

<h2>Part 1 – C++ Multimedia Server</h2>
<ul>
  <li>Implements a hierarchy of multimedia objects: <code>Photo</code>, <code>Video</code>, <code>Film</code>.</li>
  <li>Manages groups of objects using STL containers and smart pointers.</li>
  <li>Stores/retrieves objects in a database using <code>std::map</code>.</li>
  <li>Handles serialization/deserialization for persistence.</li>
  <li>Includes a <b>TCP server</b> to handle client commands: search, display, play.</li>
  <li>Robust memory management and error handling.</li>
</ul>

<h2>Part 2 – Java Swing Remote Control</h2>
<p>
The Java part provides a GUI that communicates with the C++ server.
It was implemented step by step:
</p>
<ol>
  <li>
    <b>Main Window:</b> 
    A <code>JFrame</code> containing a <code>JTextArea</code> and three buttons 
    (append text, append other text, quit).
  </li>
  <li>
    <b>Menus and Toolbar:</b> 
    A <code>JMenuBar</code> and <code>JToolBar</code> using <code>AbstractAction</code> 
    to avoid code duplication and allow keyboard shortcuts.
  </li>
  <li>
    <b>Client/Server Interaction:</b> 
    Integration with the C++ multimedia server via TCP. 
    The GUI can search for multimedia objects and trigger playback remotely.
  </li>
  <li>
    <b>Makefile:</b> 
    Both the C++ and Java parts include a Makefile, allowing compilation and execution with:
    <pre>make run</pre>
  </li>
</ol>

<h2>Project Structure</h2>
<ul>
  <li><b>cpp/</b>: C++ multimedia server</li>
  <li><b>swing/</b>: Java Swing GUI (remote control)</li>
  <li><b>README.html</b>: Project description and instructions</li>
</ul>

<h2>Build & Run</h2>
<p>
To build and run each part:
</p>
<pre>
cd cpp
make run    # builds and runs the C++ server

cd ../swing
make run    # builds and runs the Java Swing client
</pre>

<h2>Documentation</h2>
<ul>
  <li>C++ code documented with Doxygen.</li>
  <li>Java code documented with Javadoc.</li>
</ul>

<h2>Next Steps</h2>
<p>
Possible improvements:
<ul>
  <li>Enhanced GUI with tabs (<code>JTabbedPane</code>), dialogs (<code>JDialog</code>), or radio buttons.</li>
  <li>Additional remote control features (custom commands, playlists, etc.).</li>
</ul>
</p>

