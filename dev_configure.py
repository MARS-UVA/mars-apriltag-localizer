#!/usr/bin/env python3
import os
import subprocess
from pathlib import Path
from tempfile import TemporaryDirectory


def main() -> None:
    with TemporaryDirectory() as tmpdir:
        temp_path = Path(tmpdir).absolute()
        project_dir = Path(__file__).parent.absolute()
        os.chdir(temp_path)
        subprocess.run(['git', 'clone',
                        'https://github.com/AprilRobotics/apriltag.git',
                        '--recurse-submodules'])
        apriltag_dir = temp_path / 'apriltag'
        build_dir = apriltag_dir / 'build'
        build_dir.mkdir()
        os.chdir(build_dir)
        subprocess.run(['cmake',
                        f'-DCMAKE_INSTALL_PREFIX:PATH={project_dir}',
                        apriltag_dir])
        subprocess.run(['make', 'install'])


if __name__ == '__main__':
    main()
