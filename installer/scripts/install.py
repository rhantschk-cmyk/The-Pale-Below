import os
import requests
import zipfile
import subprocess

#konfiguration

DOWNLOAD_URL = "https://github.com/rhantschk-cmyk/The-Pale-Below/archive/refs/heads/main.zip"
GAME_NAME = "ThePaleBelow"

#download

home = os.path.expanduser("~")
install_dir = os.path.join(home, "Games", GAME_NAME)
zip_path = os.path.join(install_dir, "game.zip")

if not os.path.exists(install_dir):
    os.makedirs(install_dir)

response = requests.get(DOWNLOAD_URL, stream = True)

with open(zip_path, "wb") as f:
    f.write(response.content)

with zipfile.ZipFile(zip_path, 'r') as zip_ref:
    zip_ref.extractall(install_dir)

os.remove(zip_path)


