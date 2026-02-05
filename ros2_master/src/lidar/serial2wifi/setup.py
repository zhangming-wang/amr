from setuptools import find_packages, setup

package_name = "serial2wifi"

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
    maintainer="fishros",
    maintainer_email="87068644+fishros@users.noreply.github.com",
    description="TODO: Package description",
    license="TODO: License declaration",
    tests_require=["pytest"],
    entry_points={
        "console_scripts": [
            "tcpserver=serial2wifi.tcpserver:main",
            "udpserver=serial2wifi.udpserver:main",
            "serialserver=serial2wifi.serialserver:main",
        ],
    },
)
