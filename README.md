# Quantum-SymCell
Symengine wrapper for Quantum

This project demonstrates how to build a C++ plugin for Quantum. Make sure you have built all dependencies.

You can find those here: [Quantum-Installer](https://github.com/uclatommy/Quantum-Installer.git)

    git clone https://github.com/uclatommy/Quantum-Installer.git
    ./dev-install.sh
    ./create-osx-bundle.sh master
    ./setup-quantum.sh

Now you can build Quantum-SymCell:

    git clone https://github.com/uclatommy/Quantum-SymCell.git
    ./pre-build.sh
    mkdir build && cd build
    cmake ..
    make install

You should now have `libSymCell.dylib` installed to `/Applications/Quantum.app/Contents/Resources/.kivy/extensions/plugins`. Start Quantum's embedded Python interpreter:

    /Applications/Quantum.app/Contents/Resources/python
    
Import and use `libSymCell.dylib`

    import os
    import Quantum
    kernel = QuKernel()
    kernel.load_plugin(os.path.join(kernel.root_directory, 'extensions', 'plugins', 'libSymCell.dylib')
