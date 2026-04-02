import os
import requests
import zipfile

print("Welcome to the Installer of ThePaleBellow.")
confirmation = input("Do you want to continue with the Download Y/n")

#konfiguration

if confirmation == "Y" or confirmation == "":
    print("Setting up installation...")

    DOWNLOAD_URL = "https://github.com/rhantschk-cmyk/The-Pale-Below/archive/refs/heads/main.zip"
    GAME_NAME = "ThePaleBelow"

    #download

    print("Creating installation directory...")

    home = os.path.expanduser("~")
    install_dir = os.path.join(home, "Games", GAME_NAME)
    zip_path = os.path.join(install_dir, "game.zip")

    if not os.path.exists(install_dir):
        os.makedirs(install_dir)

    print("Downloading data from GitHub...")

    response = requests.get(DOWNLOAD_URL, stream = True)

    print("Unpacking data...")

    with open(zip_path, "wb") as f:
        f.write(response.content)

    with zipfile.ZipFile(zip_path, 'r') as zip_ref:
        zip_ref.extractall(install_dir)

    print("Cleaning up...")

    os.remove(zip_path)

    print("Installation complete. You can now close this window.")
else:
    print("Canceled installation.")

while True:
    pass


