from setuptools import find_packages, setup

package_name = "command"

setup(
    name=package_name,
    version="0.0.0",
    packages=find_packages(exclude=["test"]),
    data_files=[
        ("share/ament_index/resource_index/packages", ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
    ],
    install_requires=["setuptools"],
    zip_safe=True,
    maintainer="root",
    maintainer_email="18279657653@139.com",
    description="TODO: Package description",
    license="Apache-2.0",
    extras_require={
        "test": [
            "pytest",
        ],
    },
    entry_points={
        "console_scripts": [
            "init_pose = command.init_pose:main",
            "goto_pose = command.goto_pose:main",
            "waypoints_follow = command.waypoints_follow:main",
            "save_map = command.save_map:main",
        ],
    },
)
