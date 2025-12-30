from setuptools import find_packages, setup

package_name = "nav2_cmd"

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
    maintainer_email="zmwang@visionnav.com",
    description="TODO: Package description",
    license="Apache-2.0",
    extras_require={
        "test": [
            "pytest",
        ],
    },
    entry_points={
        "console_scripts": [
            "init_pose = nav2_cmd.init_pose:main",
            "goto_pose = nav2_cmd.goto_pose:main",
            "waypoints_follow = nav2_cmd.waypoints_follow:main",
        ],
    },
)
