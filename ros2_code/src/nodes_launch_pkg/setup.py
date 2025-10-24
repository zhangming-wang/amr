from setuptools import find_packages, setup
import os

package_name = "nodes_launch_pkg"

setup(
    name=package_name,
    version="0.0.0",
    packages=find_packages(exclude=["test"]),
    data_files=[
        ("share/ament_index/resource_index/packages", ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
        (os.path.join("share", package_name, "launch"), [os.path.join("launch", f) for f in os.listdir("launch")]),
        # 安装 params 文件夹
        (os.path.join("share", package_name, "params"), [os.path.join("params", f) for f in os.listdir("params")]),
    ],
    install_requires=["setuptools"],
    zip_safe=True,
    maintainer="linux",
    maintainer_email="18279657653@139.com",
    description="TODO: Package description",
    license="Apache-2.0",
    extras_require={
        "test": [
            "pytest",
        ],
    },
    entry_points={
        "console_scripts": [],
    },
)
