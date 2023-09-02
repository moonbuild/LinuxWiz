#bin/bash
set -e


packages=(jq figlet)
sudo pacman -S "${packages[@]}"

ip_address=$(curl ifconfig.me)
timezone=$(curl -s https://ipapi.co/json/$timezone | jq -r '.timezone')
sudo timedatectl set-timezone "$timezone"
show_msg "Your timezone has been updated to $timezone"

sudo pacman-key --refresh-keys
sudo pacman-key --init 
sudo pacman-key --populate
show_msg "Updated Keys"

sudo pacman -Syu
show_msg "Updated System packages, yahoo!"

yay -S pamac-aur
show_msg "Installed Pamac GUI Manager!"

programming=(git curl unzip vscodium python python-pip)
#ask
read -p "are you a programmer [Y/n]" -i "Y" answer
if [[$answer == "Y" || $answer == "y" ]]; then
  echo "Yes, okay!, Installing required packages..."
  sudo pacman -S --needed "${programming[@]}"
else
  echo "No worries, then just installing the generic tools"
  #install generic tools
fi

function show_msg {
  message = "$1"
  figlet "$message"
}