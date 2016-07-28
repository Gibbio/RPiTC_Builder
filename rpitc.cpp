#include "rpitc.h"
#include "ui_rpitc.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QProcess>

QString ica_pkgs = "not_present";
QString icah264_pkgs = "not_present";
QString vmware_pkgs = "not_present";
QString nxc_pkgs = "not_present";
QString thinlinc_pkgs = "not_present";
QString twox_pkgs = "not_present";
QString browser_pkgs = "not_present";

QString x2go_pkgs = "not_present";
QString spice_pkgs = "not_present";
QString tn5250_pkgs = "not_present";
QString tn5250j_pkgs = "not_present";
QString x3270_pkgs = "not_present";
QString xephyr_pkgs = "not_present";
QString jdk7_pkgs = "not_present";
QString jdk8_pkgs = "not_present";

QString rdesktop_pkgs = "not_present";
QString xfreerdp_pkgs = "not_present";
QString xfreerdpgit_pkgs = "not_present";
QString dfreerdp_pkgs = "not_present";

QString cups_pkgs = "not_present";
QString x11vnc_pkgs = "not_present";
QString ssh_pkgs = "not_present";
QString docky_pkgs = "not_present";
QString conky_pkgs = "not_present";
QString virtualhere_pkgs = "not_present";
QString openconnect_pkgs = "not_present";
QString openvpn_pkgs = "not_present";
QString vpnc_pkgs = "not_present";
QString bluez_pkgs = "not_present";

QString bluez_firmware_pkgs = "not_present";
QString ath_firmware_pkgs = "not_present";
QString bcm_firmware_pkgs = "not_present";
QString intel_firmware_pkgs = "not_present";
QString rtl_firmware_pkgs = "not_present";
QString zd_firmware_pkgs = "not_present";
QString ng_firmware_pkgs = "not_present";
QString b43_firmware_pkgs = "not_present";

QString overclock_pkgs = "not_present";
QString custom1_pkgs = "not_present";

QString int_bluetooth_pkgs = "not_present";
QString int_wlan_pkgs = "not_present";

RPiTC::RPiTC(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RPiTC)
{
    ui->setupUi(this);
    RPiTC::on_rescan_pushButton_clicked();
}

RPiTC::~RPiTC()
{
    delete ui;
}

void RPiTC::on_pushButton_clicked()
{
    QString bash_me = "#!/bin/bash\n####### RPi-TC Builder #######\n\n";
    if (ui->aptcache_checkBox->isChecked()) {
        bash_me = bash_me + "####### Update apt cache:\n"
                            "apt-get update\n";
    }
    QString bash_me_filename = "/opt/bashme.sh";
    ui->icah264_checkBox->setEnabled(false);

    //######################START MAIN CLIENTS INSTALL/REMOVE ROUTINES######################ßß
    if (true) {
        // CITRIX RECEIVER:
        if (ui->ica_checkBox->isChecked() && ica_pkgs == "not_present") { qDebug() << "I have to install Citrix Receiver!";
        bash_me = bash_me + "\n####### CITRIX RECEIVER Install cmds:\n"
                            "apt-get install -y icaclient ctxusb libcurl4-gnutls-dev libwebkitgtk-1.0-0\nsystemctl enable ctxusbd\n"
                            "ln -s /usr/share/ca-certificates/mozilla/* /opt/Citrix/ICAClient/keystore/cacerts/\n"
                            "c_rehash /opt/Citrix/ICAClient/keystore/cacerts/\n"
                            "#seem that eula.txt is missing from some folder... This will stop ICA client 13.3 from starting, lol\n"
                            "cp /opt/Citrix/ICAClient/nls/en.UTF-8/eula.txt /opt/Citrix/ICAClient/nls/en/\n"
                            "cp /opt/Citrix/ICAClient/nls/de.UTF-8/eula.txt /opt/Citrix/ICAClient/nls/de/\n"
                            "cp /opt/Citrix/ICAClient/nls/ru.UTF-8/eula.txt /opt/Citrix/ICAClient/nls/ru/\n"
                            "cp /opt/Citrix/ICAClient/nls/es.UTF-8/eula.txt /opt/Citrix/ICAClient/nls/es/\n"
                            "cp /opt/Citrix/ICAClient/nls/ja.UTF-8/eula.txt /opt/Citrix/ICAClient/nls/ja/\n"
                            "cp /opt/Citrix/ICAClient/nls/fr.UTF-8/eula.txt /opt/Citrix/ICAClient/nls/fr/\n"
                            "cp /opt/Citrix/ICAClient/nls/zh_HANS.UTF-8/eula.txt /opt/Citrix/ICAClient/nls/zh_CN/\n"
                            "cp /opt/Citrix/ICAClient/nls/zh_HANS.UTF-8/eula.txt /opt/Citrix/ICAClient/nls/zh_SN/\n"
                            "cp /opt/Citrix/ICAClient/nls/zh_HANS.UTF-8/eula.txt /opt/Citrix/ICAClient/nls/zh_HANS/\n"
                            "# Add ICA icon to docky menu:\n/opt/scripts/dockyadd.sh selfservice.desktop\n";
        }
        if (!ui->ica_checkBox->isChecked() && ica_pkgs == "installed") { qDebug() << "I have to remove Citrix Receiver!";
        bash_me = bash_me + "\n####### CITRIX RECEIVER Remove cmds:\n"
                            "apt-get remove --purge -y icaclient ctxusb libcurl4-gnutls-dev libwebkitgtk-1.0-0\napt-get autoremove --purge -y\nsystemctl disable ctxusbd\n"
                            "rm -fr /opt/Citrix\n"
                            "# Remove ICA icon from docky menu:\n/opt/scripts/dockyrm.sh selfservice.desktop\n";
        }
        // ICA H.264 Acceleration:
        if (ui->icah264_checkBox->isChecked() && icah264_pkgs == "not_present") { qDebug() << "I have to install ICA H.264!";
        bash_me = bash_me + "\n####### ICA H.264 Accelerated for RPi2 Install cmds:\n"
                            "#use JPEG Turbo lib:\n"
                            "mv /opt/Citrix/ICAClient/lib/ctxjpeg_fb_8.so /opt/Citrix/ICAClient/lib/ctxjpeg_fb_8.so.DO_NOT_USE\n"
                            "#new RPi2 accelerated H.264:\n"
                            "mv /opt/Citrix/ICAClient/lib/ctxh264.so /opt/Citrix/ICAClient/lib/ctxh264.so.DO_NOT_USE\n"
                            "cp /opt/libraries/ctxh264.so /opt/Citrix/ICAClient/lib/\n"
                            "#Uncomment the Citrix framebuffer options in config.txt:\n"
                            "sed -i '/^#framebuffer_depth=32/{s/^#//}' /boot/config.txt\nsed -i '/^#framebuffer_ignore_alpha=1/{s/^#//}' /boot/config.txt\n";
        }
        if (!ui->icah264_checkBox->isChecked() && icah264_pkgs == "installed") { qDebug() << "I have to remove ICA H.264!";
        bash_me = bash_me + "\n####### ICA H.264 Accelerated for RPi2 Remove cmds:\n"
                            "#Switch back to non-accelerated H.264 lib:\n"
                            "mv /opt/Citrix/ICAClient/lib/ctxh264.so.DO_NOT_USE /opt/Citrix/ICAClient/lib/ctxh264.so\n"
                            "#Switch back to standard libjpeg\n"
                            "mv /opt/Citrix/ICAClient/lib/ctxjpeg_fb_8.so.DO_NOT_USE /opt/Citrix/ICAClient/lib/ctxjpeg_fb_8.so\n"
                            "#Comment the Citrix framebuffer options in config.txt:\n"
                            "sed -i '/^framebuffer_depth=32/{s/^/#/}' /boot/config.txt\nsed -i '/^framebuffer_ignore_alpha=1/{s/^/#/}' /boot/config.txt\n";
        }
        // PARALLELS 2X:
        if (ui->twox_checkBox->isChecked() && twox_pkgs == "not_present") { qDebug() << "I have to install Parallel 2X!";
        bash_me = bash_me + "\n####### PARALLELS 2X Install cmds:\n"
                            "apt-get install -y rasclient\n"
                            "# Add 2X icon to docky menu:\n/opt/scripts/dockyadd.sh 2xclient.desktop\n";
        }
        if (!ui->twox_checkBox->isChecked() && twox_pkgs == "installed") { qDebug() << "I have to remove Parallel 2X!";
        bash_me = bash_me + "\n####### PARALLELS 2X Remove cmds:\n"
                            "apt-get remove --purge -y rasclient\n"
                            "# Remove 2X icon from docky menu:\n/opt/scripts/dockyrm.sh 2xclient.desktop\n";
        }
        // NOMACHINE NX
        if (ui->nomachine_checkBox->isChecked() && nxc_pkgs == "not_present") { qDebug() << "I have to install NoMachine!";
        bash_me = bash_me + "\n####### NOMACHINE NX Install cmds:\n"
                            "apt-get install -y xdg-user-dirs\n"
                            "wget http://dl.armtc.net/RPi-TC/packages/nxplayer.tar.gz -O /tmp/nxplayer.tar.gz\ntar xf /tmp/nxplayer.tar.gz -C /usr/\n"
                            "wget http://dl.armtc.net/RPi-TC/packages/nxclient.tar.gz -O /tmp/nxclient.tar.gz\ntar xf /tmp/nxclient.tar.gz -C /usr/\n"
                            "ln -s /usr/NX/share/applnk/client/network/nxplayer.desktop /usr/share/applications/nxplayer.desktop\n"
                            "# Add NX icon to docky menu:\n/opt/scripts/dockyadd.sh nxplayer.desktop\n";
        }
        if (!ui->nomachine_checkBox->isChecked() && nxc_pkgs == "installed") { qDebug() << "I have to remove NoMachine!";
        bash_me = bash_me + "\n####### NOMACHINE NX Remove cmds:\n"
                            "apt-get remove --purge -y xdg-user-dirs\n"
                            "rm -fr /usr/NX/ /usr/share/applications/nxplayer.desktop\n"
                            "# Remove NX icon from docky menu:\n/opt/scripts/dockyrm.sh nxplayer.desktop\n";
        }
        // VMWARE HORIZON
        if (ui->vmware_checkBox->isChecked() && vmware_pkgs == "not_present") { qDebug() << "I have to install VMWare Horizon!";
        bash_me = bash_me + "\n####### VMWARE HORIZON Install cmds:\n"
                            "apt-get install libudev1 libxss1\n"
                            "ln -s /lib/arm-linux-gnueabihf/libudev.so.1 /lib/arm-linux-gnueabihf/libudev.so.0\n"
                            "wget http://dl.armtc.net/RPi-TC/packages/vmwh410.tar.gz -O /tmp/vmwh410.tar.gz\ntar xf /tmp/vmwh410.tar.gz -C /tmp/\n/tmp/install\n"
                            "systemctl enable vmwareusbd\nsystemctl start vmwareusbd\n"
                            "# Add Horizon icon to docky menu:\n/opt/scripts/dockyadd.sh vmware-view.desktop\n";
        }
        if (!ui->vmware_checkBox->isChecked() && vmware_pkgs == "installed") { qDebug() << "I have to remove VMWare Horizon!";
        bash_me = bash_me + "\n####### VMWARE HORIZON Remove cmds:\n"
                            "rm -rf /lib/arm-linux-gnueabihf/libudev.so.0\n"
                            "systemctl disable vmwareusbd\n"
                            "find /etc/|grep -i vmware |xargs rm -fr;find /lib/|grep -i vmware |xargs rm -fr;find /usr/|grep -i vmware |xargs rm -fr;find /|grep -i pcoip |xargs rm -fr\n"
                            "# Remove Horizon icon from docky menu:\n/opt/scripts/dockyrm.sh vmware-horizon.desktop\n";
        }
        // THINLINC
        if (ui->thinlinc_checkBox->isChecked() && thinlinc_pkgs == "not_present") { qDebug() << "I have to install ThinLinc!";
        bash_me = bash_me + "\n####### THINLINC Install cmds:\n"
                            "apt-get install -y thinlinc-client\n"
                            "# Add Thinlinc icon to docky menu:\n/opt/scripts/dockyadd.sh thinlinc-client.desktop\n";
        }
        if (!ui->thinlinc_checkBox->isChecked() && thinlinc_pkgs == "installed") { qDebug() << "I have to remove ThinLinc!";
        bash_me = bash_me + "\n####### THINLINC Remove cmds:\n"
                            "apt-get remove --purge -y thinlinc-client\n"
                            "# Remove Thinlinc icon from docky menu:\n/opt/scripts/dockyrm.sh thinlinc-client.desktop\n";
        }
        // BROWSER
        if (ui->browser_checkBox->isChecked() && browser_pkgs == "not_present") { qDebug() << "I have to install Firefox!";
        bash_me = bash_me + "\n####### BROWSER Install cmds:\n"
                            "apt-get install -y firefox-esr\n"
                            "# Add Firefox icon to docky menu:\n/opt/scripts/dockyadd.sh firefox-esr.desktop\n";
        }
        if (!ui->browser_checkBox->isChecked() && browser_pkgs == "installed") { qDebug() << "I have to remove Firefox!";
        bash_me = bash_me + "\n####### BROWSER Remove cmds:\n"
                            "apt-get remove --purge -y firefox-esr\n"
                            "# Remove Firefox icon from docky menu:\n/opt/scripts/dockyrm.sh firefox-esr.desktop\n";
        }
    }
    //######################START RDP CLIENTS INSTALLATION/REMOVE ROUTINES##################ßß
    if (true) {
        // RDESKTOP
        if (ui->rdesktop_checkBox->isChecked() && rdesktop_pkgs == "not_present") { qDebug() << "I have to install RDesktop!";
        bash_me = bash_me + "\n####### RDESKTOP Install cmds:\n"
                            "apt-get install -y rdesktop pcscd\n"
                            "ln -s /opt/config/RDesktop.desktop /usr/share/applications/RDesktop.desktop\n"
                            "# Add RDesktop icon to docky menu:\n/opt/scripts/dockyadd.sh RDesktop.desktop\n";
        }
        if (!ui->rdesktop_checkBox->isChecked() && rdesktop_pkgs == "installed") { qDebug() << "I have to remove RDesktop!";
        bash_me = bash_me + "\n####### RDESKTOP Remove cmds:\n"
                            "apt-get remove --purge -y rdesktop pcscd\n"
                            "rm -fr /usr/share/applications/RDesktop.desktop\n"
                            "# Remove RDesktop icon from docky menu:\n/opt/scripts/dockyrm.sh RDesktop.desktop\n";
        }
        // XFREERDP DEB
        if (ui->xfreerdp_checkBox->isChecked() && xfreerdp_pkgs == "not_present") { qDebug() << "I have to install xFreeRDP DEB!";
        bash_me = bash_me + "\n####### XFREERDP DEB Install cmds:\n"
                            "apt-get install -y freerdp-x11 libfreerdp-plugins-standard gstreamer0.10-plugins-base\n"
                            "ln -s /opt/config/xFreeRDP.desktop /usr/share/applications/xFreeRDP.desktop\n"
                            "# Add xFreeRDP_DEB icon to docky menu:\n/opt/scripts/dockyadd.sh xFreeRDP.desktop\n";
        }
        if (!ui->xfreerdp_checkBox->isChecked() && xfreerdp_pkgs == "installed") { qDebug() << "I have to remove xFreeRDP DEB!";
        bash_me = bash_me + "\n####### XFREERDP DEB Remove cmds:\n"
                            "apt-get remove --purge -y freerdp-x11 libfreerdp-plugins-standard\n"
                            "rm -fr /usr/share/applications/xFreeRDP.desktop\n"
                            "# Remove xFreeRDP_DEB icon from docky menu:\n/opt/scripts/dockyrm.sh xFreeRDP.desktop\n";
        }
        // XFREERDP GIT
        if (ui->xfreerdpgit_checkBox->isChecked() && xfreerdpgit_pkgs == "not_present") { qDebug() << "I have to install xFreeRDP GIT!";
        bash_me = bash_me + "\n####### XFREERDP GIT Install cmds:\n"
                            "apt-get install -y libssl1.0.0\n"
                            "wget http://dl.armtc.net/RPi-TC/packages/xfreerdp_LATEST -O /usr/bin/xfreerdp_git\nchmod +x /usr/bin/xfreerdp_git\n"
                            "ln -s /opt/config/xFreeRDP_GIT.desktop /usr/share/applications/xFreeRDP_GIT.desktop\n"
                            "# Add xFreeRDP_GIT icon to docky menu:\n/opt/scripts/dockyadd.sh xFreeRDP_GIT.desktop\n";
        }
        if (!ui->xfreerdpgit_checkBox->isChecked() && xfreerdpgit_pkgs == "installed") { qDebug() << "I have to remove xFreeRDP GIT!";
        bash_me = bash_me + "\n####### XFREERDP GIT Remove cmds:\n"
                            "rm -fr /usr/share/applications/xFreeRDP_GIT.desktop /usr/bin/xfreerdp_git\n"
                            "# Remove xFreeRDP_GIT icon from docky menu:\n/opt/scripts/dockyrm.sh xFreeRDP_GIT.desktop\n";
        }
        // DFREERDP
        if (ui->dfreerdp_checkBox->isChecked() && dfreerdp_pkgs == "not_present") { qDebug() << "I have to install dFreeRDP!";
        bash_me = bash_me + "\n####### DFREERDP Install cmds:\n"
                            "apt-get install -y dfreerdp\n"
                            "ln -s /opt/config/fb.modes /etc/fb.modes;ln -s /opt/config/directfbrc /etc/directfbrc\n"
                            "ln -s /opt/config/dFreeRDP.desktop /usr/share/applications/dFreeRDP.desktop\n"
                            "# Add dFreeRDP icon to docky menu:\n/opt/scripts/dockyadd.sh dFreeRDP.desktop\n";
        }
        if (!ui->dfreerdp_checkBox->isChecked() && dfreerdp_pkgs == "installed") { qDebug() << "I have to remove dFreeRDP!";
        bash_me = bash_me + "\n####### DFREERDP Remove cmds:\n"
                            "rm -fr /etc/fb.modes /etc/directfbrc /usr/share/applications/dFreeRDP.desktop\n"
                            "apt-get remove --purge -y dfreerdp\n"
                            "# Remove dFreeRDP icon from docky menu:\n/opt/scripts/dockyrm.sh dFreeRDP.desktop\n";
        }
    }
    //######################START OTHER CLIENTS INSTALLATION/REMOVE ROUTINES################ßß
    if (true) {
        // X2GO CLIENT:
        if (ui->x2go_checkBox->isChecked() && x2go_pkgs == "not_present") { qDebug() << "I have to install x2go client!";
        bash_me = bash_me + "\n####### X2GO CLIENT Install cmds:\n"
                            "apt-get install -y x2goclient\n"
                            "# Add X2GO icon to docky menu:\n/opt/scripts/dockyadd.sh x2goclient.desktop\n";
        }
        if (!ui->x2go_checkBox->isChecked() && x2go_pkgs == "installed") { qDebug() << "I have to remove x2go client!";
        bash_me = bash_me + "\n####### X2GO CLIENT Remove cmds:\n"
                            "apt-get remove --purge -y x2goclient\n"
                            "# Remove X2GO icon from docky menu:\n/opt/scripts/dockyrm.sh x2goclient.desktop\n";
        }
        // SPICE
        if (ui->spice_checkBox->isChecked() && spice_pkgs == "not_present") { qDebug() << "I have to install spice client!";
        bash_me = bash_me + "\n####### SPICE CLIENT Install cmds:\n"
                            "wget http://dl.armtc.net/RPi-TC/packages/SpiceGTK.tar.gz -O /tmp/SpiceGTK.tar.gz\ntar xf /tmp/SpiceGTK.tar.gz -C /opt/\n"
                            "ln -s /opt/config/spicegtk.desktop /usr/share/applications/spicegtk.desktop\n"
                            "# Add SPICE icon to docky menu:\n/opt/scripts/dockyadd.sh spicegtk.desktop\n";
        }
        if (!ui->spice_checkBox->isChecked() && spice_pkgs == "installed") { qDebug() << "I have to remove spice client!";
        bash_me = bash_me + "\n####### SPICE CLIENT Remove cmds:\n"
                            "rm -fr /opt/SpiceGTK/ /usr/share/applications/spicegtk.desktop\n"
                            "# Remove SPICE icon from docky menu:\n/opt/scripts/dockyrm.sh spicegtk.desktop\n";
        }
        // TN5250
        if (ui->tn5250_checkBox->isChecked() && tn5250_pkgs == "not_present") { qDebug() << "I have to install TN5250!";
        bash_me = bash_me + "\n####### TN5250 Install cmds:\n"
                            "apt-get install -y tn5250\n"
                            "ln -s /opt/config/tn5250.desktop /usr/share/applications/tn5250.desktop\n"
                            "# Add TN5250 icon to docky menu:\n/opt/scripts/dockyadd.sh tn5250.desktop\n";
        }
        if (!ui->tn5250_checkBox->isChecked() && tn5250_pkgs == "installed") { qDebug() << "I have to remove TN5250!";
        bash_me = bash_me + "\n####### TN5250 Remove cmds:\n"
                            "apt-get remove --purge -y tn5250\n"
                            "rm -fr /usr/share/applications/tn5250.desktop\n"
                            "# Remove TN5250 icon from docky menu:\n/opt/scripts/dockyrm.sh tn5250.desktop\n";
        }
        // TN5250J
        if (ui->tn5250j_checkBox->isChecked() && tn5250j_pkgs == "not_present") { qDebug() << "I have to install TN5250J!";
        bash_me = bash_me + "\n####### TN5250J Install cmds:\n"
                            "wget http://dl.armtc.net/RPi-TC/packages/tn5250j-0.7.6-full-bin.zip -O /opt/tn5250j-0.7.6-full-bin.zip\n"
                            "unzip /opt/tn5250j-0.7.6-full-bin.zip -d /opt/\nrm -fr /opt/tn5250j-0.7.6-full-bin.zip\n"
                            "ln -s /opt/config/tn5250j.desktop /usr/share/applications/tn5250j.desktop\n"
                            "# Add TN5250J icon to docky menu:\n/opt/scripts/dockyadd.sh tn5250j.desktop\n";
        }
        if (!ui->tn5250j_checkBox->isChecked() && tn5250j_pkgs == "installed") { qDebug() << "I have to remove TN5250J!";
        bash_me = bash_me + "\n####### TN5250J Remove cmds:\n"
                            "rm -fr /opt/tn5250j-0.7.6\nrm -fr /usr/share/applications/tn5250j.desktop\n"
                            "# Remove TN5250 icon from docky menu:\n/opt/scripts/dockyrm.sh tn5250j.desktop\n";
        }
        // x3270
        if (ui->x3270_checkBox->isChecked() && x3270_pkgs == "not_present") { qDebug() << "I have to install x3270!";
        bash_me = bash_me + "\n####### x3270 Install cmds:\n"
                            "apt-get install -y suite3270\n"
                            "ln -s /opt/config/x3270.desktop /usr/share/applications/x3270.desktop\n"
                            "# Add x3270 icon to docky menu:\n/opt/scripts/dockyadd.sh x3270.desktop\n";
        }
        if (!ui->x3270_checkBox->isChecked() && x3270_pkgs == "installed") { qDebug() << "I have to remove x3270!";
        bash_me = bash_me + "\n####### x3270 Remove cmds:\n"
                            "apt-get remove --purge -y suite3270\n"
                            "rm -fr /usr/share/applications/x3270.desktop\n"
                            "# Remove x3270 icon from docky menu:\n/opt/scripts/dockyrm.sh x3270.desktop\n";
        }
        // XEPHYR
        if (ui->xephyr_checkBox->isChecked() && xephyr_pkgs == "not_present") { qDebug() << "I have to install Xephyr!";
        bash_me = bash_me + "\n####### XEPHYR Install cmds:\n"
                            "apt-get install -y xserver-xephyr\n"
                            "ln -s /opt/config/Xephyr.desktop /usr/share/applications/Xephyr.desktop\n"
                            "# Add Xephyr icon to docky menu:\n/opt/scripts/dockyadd.sh Xephyr.desktop\n";
        }
        if (!ui->xephyr_checkBox->isChecked() && xephyr_pkgs == "installed") { qDebug() << "I have to remove Xephyr!";
        bash_me = bash_me + "\n####### XEPHYR Remove cmds:\n"
                            "apt-get remove --purge -y xserver-xephyr\n"
                            "rm -fr /usr/share/applications/Xephyr.desktop\n"
                            "# Remove Xephyr icon from docky menu:\n/opt/scripts/dockyrm.sh Xephyr.desktop\n";
        }
        // ORACLE-JAVA7-JDK
        if (ui->jdk7_checkBox->isChecked() && jdk7_pkgs == "not_present") { qDebug() << "I have to install ORACLE-JAVA7-JDK!";
        bash_me = bash_me + "\n####### ORACLE-JAVA7-JDK Install cmds:\n"
                            "mkdir -p /usr/share/man/man1/\n"
                            "apt-get install -y oracle-java7-jdk\n";
        }
        if (!ui->jdk7_checkBox->isChecked() && jdk7_pkgs == "installed") { qDebug() << "I have to remove ORACLE-JAVA7-JDK!";
        bash_me = bash_me + "\n####### ORACLE-JAVA7-JDK Remove cmds:\n"
                            "apt-get remove --purge -y oracle-java7-jdk\n"
                            "rm -fr /usr/share/man/man1/\n";
        }
        // ORACLE-JAVA8-JDK
        if (ui->jdk8_checkBox->isChecked() && jdk8_pkgs == "not_present") { qDebug() << "I have to install ORACLE-JAVA8-JDK!";
        bash_me = bash_me + "\n####### ORACLE-JAVA8-JDK Install cmds:\n"
                            "mkdir -p /usr/share/man/man1/\n"
                            "apt-get install -y oracle-java8-jdk\n";
        }
        if (!ui->jdk8_checkBox->isChecked() && jdk8_pkgs == "installed") { qDebug() << "I have to remove ORACLE-JAVA8-JDK!";
        bash_me = bash_me + "\n####### ORACLE-JAVA8-JDK Remove cmds:\n"
                            "apt-get remove --purge -y oracle-java8-jdk\n"
                            "rm -fr /usr/share/man/man1/\n";
        }
    }
    //######################START OS SERVICES INSTALLATION/REMOVE ROUTINES##################ßß
    if (true) {
        // CUPS
        if (ui->cups_checkBox->isChecked() && cups_pkgs == "not_present") { qDebug() << "I have to install CUPS!";
        bash_me = bash_me + "\n####### CUPS Install cmds:\n"
                            "apt-get install -y cups cups-browsed printer-driver-gutenprint\n";
        }
        if (!ui->cups_checkBox->isChecked() && cups_pkgs == "installed") { qDebug() << "I have to remove CUPS!";
        bash_me = bash_me + "\n####### CUPS Remove cmds:\n"
                            "apt-get remove --purge -y cups cups-common cups-browsed printer-driver-gutenprint\n";
        }
        // X11VNC
        if (ui->vnc_checkBox->isChecked() && x11vnc_pkgs == "not_present") { qDebug() << "I have to install X11VNC Server!";
        bash_me = bash_me + "\n####### X11VNC Install cmds:\n"
                            "apt-get install -y x11vnc\n"
                            "\n# set vnc server default password to rpitc:\n"
                            "x11vnc -storepasswd rpitc /home/rpitc/.x11vnc/passwd";
        }
        if (!ui->vnc_checkBox->isChecked() && x11vnc_pkgs == "installed") { qDebug() << "I have to remove X11VNC Server!";
        bash_me = bash_me + "\n####### X11VNC Remove cmds:\n"
                            "apt-get remove --purge -y x11vnc\n";
        }
        // SSH
        if (ui->ssh_checkBox->isChecked() && ssh_pkgs == "not_present") { qDebug() << "I have to install SSH Server!";
        bash_me = bash_me + "\n####### SSH Install cmds:\n"
                            "apt-get install -y openssh-server\n";
        }
        if (!ui->ssh_checkBox->isChecked() && ssh_pkgs == "installed") { qDebug() << "I have to remove SSH Server!";
        bash_me = bash_me + "\n####### SSH Remove cmds:\n"
                            "apt-get remove --purge -y openssh-server\n";
        }
        // DOCKY
        if (ui->docky_checkBox->isChecked() && docky_pkgs == "not_present") { qDebug() << "I have to install Docky!";
        bash_me = bash_me + "\n####### DOCKY Install cmds:\n"
                            "apt-get install -y docky\n";
        }
        if (!ui->docky_checkBox->isChecked() && docky_pkgs == "installed") { qDebug() << "I have to remove Docky!";
        bash_me = bash_me + "\n####### DOCKY Remove cmds:\n"
                            "apt-get remove --purge -y docky\n";
        }
        // CONKY
        if (ui->conky_checkBox->isChecked() && conky_pkgs == "not_present") { qDebug() << "I have to install Conky!";
        bash_me = bash_me + "\n####### CONKY Install cmds:\n"
                            "apt-get install -y conky\n"
                            "cp /opt/config/Conky.autostart /home/rpitc/.config/autostart/\n";
        }
        if (!ui->conky_checkBox->isChecked() && conky_pkgs == "installed") { qDebug() << "I have to remove Conky!";
        bash_me = bash_me + "\n####### CONKY Remove cmds:\n"
                            "apt-get remove --purge -y conky\n";
        }
        // VIRTUALHERE
        if (ui->virtualhere_checkBox->isChecked() && virtualhere_pkgs == "not_present") { qDebug() << "I have to install VirtualHere USB Server!";
        bash_me = bash_me + "\n####### VIRTUALHERE Install cmds:\n"
                            "wget https://www.virtualhere.com/sites/default/files/usbserver/vhusbdarmpi2 -O /usr/bin/vhusbdarmpi2\nchmod +x /usr/bin/vhusbdarmpi2\n"
                            "cp /opt/scripts/vhusbdarmpi2 /etc/init.d/\nsystemctl enable vhusbdarmpi2;systemctl start vhusbdarmpi2\n";
        }
        if (!ui->virtualhere_checkBox->isChecked() && virtualhere_pkgs == "installed") { qDebug() << "I have to remove VirtualHere USB Server!";
        bash_me = bash_me + "\n####### VIRTUALHERE Remove cmds:\n"
                            "systemctl stop vhusbdarmpi2;systemctl disable vhusbdarmpi2;rm -fr /usr/bin/vhusbdarmpi2 /etc/init.d/vhusbdarmpi2\n";
        }
        // OPENCONNECT
        if (ui->openconnect_checkBox->isChecked() && openconnect_pkgs == "not_present") { qDebug() << "I have to install Openconnect VPN!";
        bash_me = bash_me + "\n####### OPENCONNECT Install cmds:\n"
                            "apt-get install -y openconnect network-manager-openconnect network-manager-openconnect-gnome\n";
        }
        if (!ui->openconnect_checkBox->isChecked() && openconnect_pkgs == "installed") { qDebug() << "I have to remove Openconnect VPN!";
        bash_me = bash_me + "\n####### OPENCONNECT Remove cmds:\n"
                            "apt-get remove --purge -y openconnect network-manager-openconnect network-manager-openconnect-gnome\n";
        }
        // OPENVPN
        if (ui->openvpn_checkBox->isChecked() && openvpn_pkgs == "not_present") { qDebug() << "I have to install OpenVPN!";
        bash_me = bash_me + "\n####### OPENVPN Install cmds:\n"
                            "apt-get install -y openvpn network-manager-openvpn network-manager-openvpn-gnome\n";
        }
        if (!ui->openvpn_checkBox->isChecked() && openvpn_pkgs == "installed") { qDebug() << "I have to remove OpenVPN!";
        bash_me = bash_me + "\n####### OPENVPN Remove cmds:\n"
                            "apt-get remove --purge -y openvpn network-manager-openvpn network-manager-openvpn-gnome\n";
        }
        // VPNC
        if (ui->vpnc_checkBox->isChecked() && vpnc_pkgs == "not_present") { qDebug() << "I have to install VPNC!";
        bash_me = bash_me + "\n####### VPNC Install cmds:\n"
                            "apt-get install -y vpnc network-manager-vpnc network-manager-vpnc-gnome\n";
        }
        if (!ui->vpnc_checkBox->isChecked() && vpnc_pkgs == "installed") { qDebug() << "I have to remove VPNC!";
        bash_me = bash_me + "\n####### VPNC Remove cmds:\n"
                            "apt-get remove --purge -y network-manager-vpnc network-manager-vpnc-gnome\n";
        }
        // BLUEZ
        if (ui->bluez_checkBox->isChecked() && bluez_pkgs == "not_present") { qDebug() << "I have to install BLUEZ!";
        bash_me = bash_me + "\n####### BLUEZ Install cmds:\n"
                            "apt-get install -y bluez bluez-cups bluez-tools\n";
        }
        if (!ui->bluez_checkBox->isChecked() && bluez_pkgs == "installed") { qDebug() << "I have to remove BLUEZ!";
        bash_me = bash_me + "\n####### BLUEZ Remove cmds:\n"
                            "apt-get remove --purge -y bluez bluez-cups bluez-tools\n";
        }
    }
    //######################INTERNAL BOARD HARDWARE ##################ßß
    if (true) {
        // OVERCLOCK
        if (ui->overclock_checkBox->isChecked() && overclock_pkgs == "not_present") { qDebug() << "I have to enable the overclock!";
        bash_me = bash_me + "\n####### Enabling OVERCLOCK: \n"
                            "sed -i '/^#arm_freq/{s/^#//}' /boot/config.txt\n"
                            "sed -i '/^#sdram_freq/{s/^#//}' /boot/config.txt\n"
                            "sed -i '/^#core_freq/{s/^#//}' /boot/config.txt\n"
                            "sed -i '/^#over_voltage/{s/^#//}' /boot/config.txt\n"
                            "sed -i '/^#initial_turbo/{s/^#//}' /boot/config.txt\n";
        }
        if (!ui->overclock_checkBox->isChecked() && overclock_pkgs == "installed") { qDebug() << "I have to remove the overclock!";
        bash_me = bash_me + "\n####### Disabling OVERCLOCK: \n"
                            "sed -i '/^arm_freq/{s/^/#/}' /boot/config.txt\n"
                            "sed -i '/^sdram_freq/{s/^/#/}' /boot/config.txt\n"
                            "sed -i '/^core_freq/{s/^/#/}' /boot/config.txt\n"
                            "sed -i '/^over_voltage/{s/^/#/}' /boot/config.txt\n"
                            "sed -i '/^initial_turbo/{s/^/#/}' /boot/config.txt\n";
        }
        //BLUETOOTH INTERNAL ADAPTER
        if (ui->bluetooth_checkBox->isChecked() && int_bluetooth_pkgs == "not_present") { qDebug() << "I have to enable the internal BT adapter!";
        bash_me = bash_me + "\n####### RaspberryPi3 Internal Bluetooth adapter install cmds:\n"
                            "A patch for the internal bt is needed... lol fail!\n"
                            "rm -fr /tmp/*.deb\n"
                            "wget http://archive.raspberrypi.org/debian/pool/main/b/bluez/libbluetooth3_5.23-2+rpi2_armhf.deb -O /tmp/libbluetooth3_5.23-2+rpi2_armhf.deb\n"
                            "wget http://archive.raspberrypi.org/debian/pool/main/b/bluez/bluez_5.23-2+rpi2_armhf.deb -O /tmp/bluez_5.23-2+rpi2_armhf.deb\n"
                            "wget http://archive.raspberrypi.org/debian/pool/main/b/bluez/bluetooth_5.23-2+rpi2_all.deb -O /tmp/bluetooth_5.23-2+rpi2_all.deb\n"
                            "wget http://archive.raspberrypi.org/debian/pool/main/b/bluez/bluez-hcidump_5.23-2+rpi2_armhf.deb -O /tmp/bluez-hcidump_5.23-2+rpi2_armhf.deb\n"
                            "dpkg -i /tmp/*.deb\n"
                            "apt-get install -y pi-bluetooth pulseaudio-module-bluetooth\n"
                            "wget http://dl.armtc.net/RPi-TC/packages/bluetooth-ui.tar.gz -O /tmp/bluetooth-ui.tar.gz\ntar xf /tmp/bluetooth-ui.tar.gz -C /\n"
                            "# Add Bluetooth-UI icon to docky system menu:\n/opt/scripts/dockyadd_sys.sh bluetooth-ui.desktop\n";
        }
        if (!ui->bluetooth_checkBox->isChecked() && int_bluetooth_pkgs == "installed") { qDebug() << "I have to disable the internal BT adapter!";
        bash_me = bash_me + "\n####### RaspberryPi3 Internal Bluetooth adapter cmds:\n"
                            "apt-get remove --purge -y pi-bluetooth bluez pulseaudio-module-bluetooth\n"
                            "# Remove Bluetooth-UI icon from docky sys menu:\n/opt/scripts/dockyrm_sys.sh bluetooth-ui.desktop\n"
                            "rm -fr /usr/share/unity-control-center/pin-code-database.xml /usr/share/unity-control-center/wizard.ui /usr/bin/bluetooth-wizard /usr/share/applications/bluetooth-ui.desktop /usr/bin/bluetooth-wizard /usr/lib/arm-linux-gnueabihf/libgnome-bluetooth.so.0 /usr/lib/arm-linux-gnueabihf/libgnome-bluetooth.so.0.0.0\n";
        }
        //WLAN INTERNAL ADAPTER
        if (ui->wireless_checkBox->isChecked() && int_wlan_pkgs == "not_present") { qDebug() << "I have to enable the internal WLAN adapter!";
        bash_me = bash_me + "\n####### RaspberryPi3 Internal WLAN adapter install cmds:\n"
                            "mkdir -p /lib/firmware/brcm/\n"
                            "ln -s /opt/binaries/brcmfmac43430-sdio.txt /lib/firmware/brcm/brcmfmac43430-sdio.txt\n"
                            "ln -s /opt/binaries/brcmfmac43430-sdio.bin /lib/firmware/brcm/brcmfmac43430-sdio.bin\n";
        }
        if (!ui->wireless_checkBox->isChecked() && int_wlan_pkgs == "installed") { qDebug() << "I have to disable the internal WLAN adapter!";
        bash_me = bash_me + "\n####### RaspberryPi3 Internal WLAN adapter cmds:\n"
                            "rm -fr /lib/firmware/brcm/brcmfmac43430-sdio.txt /lib/firmware/brcm/brcmfmac43430-sdio.bin\n";
        }
    }
    //######################START CUSTOM/OTHER SERVICES INSTALLATION/REMOVE ROUTINES##################ßß
    if (true) {
        // UPDATE RPITC BUILDER
        if (ui->update_checkBox->isChecked()) { qDebug() << "UPDATE RPITC BUILDER!!";
            //clean bashme.sh and apply the update script!
            bash_me = "########### UPDATE RPITC BUILDER ###########\n"
                      "#Close the RPiTC before update:\n"
                      "killall -9 RPiTC\n"
                      "#get lastest version from GIT:\n"
                      "wget https://raw.githubusercontent.com/Gibbio/RPiTC_Builder/master/RPiTC_armhf -O /opt/binaries/RPiTC\n"
                      "#restart RPiTC and close this xterm window:\n"
                      "/opt/binaries/RPiTC &\n"
                      "exit\n";
        }
        // CUSTOM
        if (ui->custom_checkBox->isChecked() && custom1_pkgs == "not_present") { qDebug() << "I have to install CUSTOM1!";
        bash_me = bash_me + "\n\n####### Customscript: \n" + ui->custom_textEdit->toPlainText();
        }
        if (!ui->custom_checkBox->isChecked() && custom1_pkgs == "installed") { qDebug() << "I have to remove CUSTOM1!";
        bash_me = bash_me + "\n\n####### Customscript: \n" + ui->custom_textEdit->toPlainText();
        }
        // BLUEZ-FIRMWARE
        if (ui->bluez_firmware_checkBox->isChecked() && bluez_firmware_pkgs == "not_present") { qDebug() << "I have to install BLUEZ-FIRMWARE!";
        bash_me = bash_me + "\n####### BLUEZ-FIRMWARE Install cmds:\n"
                            "apt-get install -y bluez-firmware\n";
        }
        if (!ui->bluez_firmware_checkBox->isChecked() && bluez_firmware_pkgs == "installed") { qDebug() << "I have to remove BLUEZ-FIRMWARE!";
        bash_me = bash_me + "\n####### BLUEZ-FIRMWARE Remove cmds:\n"
                            "apt-get remove --purge -y bluez-firmware\n";
        }
        // ATHEROS-FIRMWARE
        if (ui->ath_firmware_checkBox->isChecked() && ath_firmware_pkgs == "not_present") { qDebug() << "I have to install ATHEROS-FIRMWARE!";
        bash_me = bash_me + "\n####### ATHEROS-FIRMWARE Install cmds:\n"
                            "apt-get install -y firmware-atheros\n";
        }
        if (!ui->ath_firmware_checkBox->isChecked() && ath_firmware_pkgs == "installed") { qDebug() << "I have to remove ATHEROS-FIRMWARE!";
        bash_me = bash_me + "\n####### ATHEROS-FIRMWARE Remove cmds:\n"
                            "apt-get remove --purge -y firmware-atheros\n";
        }
        // BCM-FIRMWARE
        if (ui->bcm_firmware_checkBox->isChecked() && bcm_firmware_pkgs == "not_present") { qDebug() << "I have to install BCM-FIRMWARE!";
        bash_me = bash_me + "\n####### BCM-FIRMWARE Install cmds:\n"
                            "apt-get install -y firmware-brcm80211\n";
        }
        if (!ui->bcm_firmware_checkBox->isChecked() && bcm_firmware_pkgs == "installed") { qDebug() << "I have to remove BCM-FIRMWARE!";
        bash_me = bash_me + "\n####### BCM-FIRMWARE Remove cmds:\n"
                            "apt-get remove --purge -y firmware-brcm80211\n";
        }
        // INTEL-FIRMWARE
        if (ui->intel_firmware_checkBox->isChecked() && intel_firmware_pkgs == "not_present") { qDebug() << "I have to install INTEL-FIRMWARE!";
        bash_me = bash_me + "\n####### INTEL-FIRMWARE Install cmds:\n"
                            "apt-get install -y firmware-ipw2x00\n";
        }
        if (!ui->intel_firmware_checkBox->isChecked() && intel_firmware_pkgs == "installed") { qDebug() << "I have to remove INTEL-FIRMWARE!";
        bash_me = bash_me + "\n####### INTEL-FIRMWARE Remove cmds:\n"
                            "apt-get remove --purge -y firmware-ipw2x00\n";
        }
        // REALTEK-FIRMWARE
        if (ui->rtl_firmware_checkBox->isChecked() && rtl_firmware_pkgs == "not_present") { qDebug() << "I have to install REALTEK-FIRMWARE!";
        bash_me = bash_me + "\n####### REALTEK-FIRMWARE Install cmds:\n"
                            "apt-get install -y firmware-realtek\n";
        }
        if (!ui->rtl_firmware_checkBox->isChecked() && rtl_firmware_pkgs == "installed") { qDebug() << "I have to remove REALTEK-FIRMWARE!";
        bash_me = bash_me + "\n####### REALTEK-FIRMWARE Remove cmds:\n"
                            "apt-get remove --purge -y firmware-realtek\n";
        }
        // ZD-FIRMWARE
        if (ui->zd_firmware_checkBox->isChecked() && zd_firmware_pkgs == "not_present") { qDebug() << "I have to install ZD-FIRMWARE!";
        bash_me = bash_me + "\n####### ZD-FIRMWARE Install cmds:\n"
                            "apt-get install -y firmware-zd1211\n";
        }
        if (!ui->zd_firmware_checkBox->isChecked() && zd_firmware_pkgs == "installed") { qDebug() << "I have to remove ZD-FIRMWARE!";
        bash_me = bash_me + "\n####### ZD-FIRMWARE Remove cmds:\n"
                            "apt-get remove --purge -y firmware-zd1211\n";
        }
        // NG-FIRMWARE
        if (ui->ng_firmware_checkBox->isChecked() && ng_firmware_pkgs == "not_present") { qDebug() << "I have to install NG-FIRMWARE!";
        bash_me = bash_me + "\n####### NG-FIRMWARE Install cmds:\n"
                            "apt-get install -y linux-wlan-ng-firmware\n";
        }
        if (!ui->ng_firmware_checkBox->isChecked() && ng_firmware_pkgs == "installed") { qDebug() << "I have to remove NG-FIRMWARE!";
        bash_me = bash_me + "\n####### NG-FIRMWARE Remove cmds:\n"
                            "apt-get remove --purge -y linux-wlan-ng-firmware\n";
        }
        // B43-FIRMWARE
        if (ui->b43_firmware_checkBox->isChecked() && b43_firmware_pkgs == "not_present") { qDebug() << "I have to install B43-FIRMWARE!";
        bash_me = bash_me + "\n####### B43-FIRMWARE Install cmds:\n"
                            "apt-get install -y firmware-b43-installer\n";
        }
        if (!ui->b43_firmware_checkBox->isChecked() && b43_firmware_pkgs == "installed") { qDebug() << "I have to remove B43-FIRMWARE!";
        bash_me = bash_me + "\n####### B43-FIRMWARE Remove cmds:\n"
                            "apt-get remove --purge -y firmware-b43-installer\n";
        }
    }

    //#### default commands to execute at the end:
    if (ui->aptcache_checkBox->isChecked()) {
        bash_me = bash_me + "\n\n####### clean up all the unecessary package and the apt-get cache:\n"
                            "apt-get autoremove --purge -y\napt-get clean\n";
    }
    bash_me = bash_me + "\n\n####### Send sync to flush the file system buffers\n"
                        "sync";

    //finalizing bash me and putting it to file:
    QFile file(bash_me_filename);
    file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream WriteOut(&file);
    WriteOut << bash_me+"\n";
    file.close();
    system(qPrintable("chmod +x "+bash_me_filename));
    bash_me = "";
    HelperWindow bashmenow;
    bashmenow.exec();
}

void RPiTC::on_rescan_pushButton_clicked()
{
    //######################START MAIN CLIENTS CHECK#####################ßß
    if (true) {
        // CITRIX RECEIVER:
        if (QFile("/opt/Citrix/ICAClient/wfica").exists()) {
            qDebug() << "Citrix Receiver is installed"; ui->ica_checkBox->setChecked(true); ica_pkgs = "installed";
            ui->icah264_checkBox->setEnabled(true);
        } else {
            qDebug() << "Citrix Receiver missing"; ui->ica_checkBox->setChecked(false); ica_pkgs = "not_present";
            ui->icah264_checkBox->setEnabled(false);
        }
        // ICA H.264:
        if (QFile("/opt/Citrix/ICAClient/lib/ctxh264.so.DO_NOT_USE").exists()) {
            qDebug() << "ICA H.264 is installed"; ui->icah264_checkBox->setChecked(true); icah264_pkgs = "installed";
        } else {
            qDebug() << "ICA H.264 missing"; ui->icah264_checkBox->setChecked(false); icah264_pkgs = "not_present";
        }
        // VMWARE HORIZON:
        if (QFile("/usr/bin/vmware-view").exists()) {
            qDebug() << "VMWare Horizon is installed"; ui->vmware_checkBox->setChecked(true); vmware_pkgs = "installed";
        } else {
            qDebug() << "VMWare Horizon missing"; ui->vmware_checkBox->setChecked(false); vmware_pkgs = "not_present";
        }
        // NOMACHINENX:
        if (QFile("/usr/NX/bin/nxplayer.bin").exists()) {
            qDebug() << "NoMachine NX is installed"; ui->nomachine_checkBox->setChecked(true); nxc_pkgs = "installed";
        } else {
            qDebug() << "NoMachine NX missing"; ui->nomachine_checkBox->setChecked(false); nxc_pkgs = "not_present";
        }
        // THINLINC:
        if (QFile("/opt/thinlinc/bin/tlclient").exists()) {
            qDebug() << "Thinlinc is installed"; ui->thinlinc_checkBox->setChecked(true); thinlinc_pkgs = "installed";
        } else {
            qDebug() << "Thinlinc missing"; ui->thinlinc_checkBox->setChecked(false); thinlinc_pkgs = "not_present";
        }
        // PARALLELS 2X:
        if (QFile("/opt/2X/Client/bin/appserverclient").exists()) {
            qDebug() << "Parallels 2X is installed"; ui->twox_checkBox->setChecked(true); twox_pkgs = "installed";
        } else {
            qDebug() << "Parallels 2X missing"; ui->twox_checkBox->setChecked(false); twox_pkgs = "not_present";
        }
        // FIREFOX:
        if (QFile("/usr/bin/firefox").exists()) {
            qDebug() << "Firefox is installed"; ui->browser_checkBox->setChecked(true); browser_pkgs = "installed";
        } else {
            qDebug() << "Firefox missing"; ui->browser_checkBox->setChecked(false); browser_pkgs = "not_present";
        }
    }
    //######################START OTHER CLIENTS CHECK####################ßß
    if (true) {
        // X2GO CLIENT:
        if (QFile("/usr/bin/x2goclient").exists()) {
            qDebug() << "X2GO Client is installed"; ui->x2go_checkBox->setChecked(true); x2go_pkgs = "installed";
        } else {
            qDebug() << "X2GO Client Receiver missing"; ui->x2go_checkBox->setChecked(false); x2go_pkgs = "not_present";
        }
        // SPICE
        if (QFile("/opt/SpiceGTK/bin/remote-viewer").exists()) {
            qDebug() << "SPICE is installed"; ui->spice_checkBox->setChecked(true); spice_pkgs = "installed";
        } else {
            qDebug() << "SPICE missing"; ui->spice_checkBox->setChecked(false); spice_pkgs = "not_present";
        }
        // TN5250
        if (QFile("/usr/bin/tn5250").exists()) {
            qDebug() << "TN5250 is installed"; ui->tn5250_checkBox->setChecked(true); tn5250_pkgs = "installed";
        } else {
            qDebug() << "TN5250 missing"; ui->tn5250_checkBox->setChecked(false); tn5250_pkgs = "not_present";
        }
        // TN5250J
        if (QFile("/opt/tn5250j-0.7.6/tn5250j.jar").exists()) {
            qDebug() << "TN5250J is installed"; ui->tn5250j_checkBox->setChecked(true); tn5250j_pkgs = "installed";
        } else {
            qDebug() << "TN5250J missing"; ui->tn5250j_checkBox->setChecked(false); tn5250j_pkgs = "not_present";
        }
        // x3270
        if (QFile("/usr/bin/x3270").exists()) {
            qDebug() << "x3270 is installed"; ui->x3270_checkBox->setChecked(true); x3270_pkgs = "installed";
        } else {
            qDebug() << "x3270 missing"; ui->x3270_checkBox->setChecked(false); x3270_pkgs = "not_present";
        }
        // XEPHYR
        if (QFile("/usr/bin/Xephyr").exists()) {
            qDebug() << "Xephyr is installed"; ui->xephyr_checkBox->setChecked(true); xephyr_pkgs = "installed";
        } else {
            qDebug() << "Xephyr missing"; ui->xephyr_checkBox->setChecked(false); xephyr_pkgs = "not_present";
        }
        // ORACLE-JAVA7-JDK
        if (QFile("/usr/share/doc/oracle-java7-jdk/copyright").exists()) {
            qDebug() << "ORACLE-JAVA7-JDK is installed"; ui->jdk7_checkBox->setChecked(true); jdk7_pkgs = "installed";
        } else {
            qDebug() << "ORACLE-JAVA7-JDK missing"; ui->jdk7_checkBox->setChecked(false); jdk7_pkgs = "not_present";
        }
        // ORACLE-JAVA8-JDK
        if (QFile("/usr/share/doc/oracle-java8-jdk/copyright").exists()) {
            qDebug() << "ORACLE-JAVA8-JDK is installed"; ui->jdk8_checkBox->setChecked(true); jdk8_pkgs = "installed";
        } else {
            qDebug() << "ORACLE-JAVA8-JDK missing"; ui->jdk8_checkBox->setChecked(false); jdk8_pkgs = "not_present";
        }
    }
    //######################START RDP CLIENTS CHECK######################ßß
    if (true) {
        // RDESKTOP
        if (QFile("/usr/bin/rdesktop").exists()) {
            qDebug() << "RDesktop is installed"; ui->rdesktop_checkBox->setChecked(true); rdesktop_pkgs = "installed";
        } else {
            qDebug() << "RDesktop missing"; ui->rdesktop_checkBox->setChecked(false); rdesktop_pkgs = "not_present";
        }
        // XFREERDP DEB
        if (QFile("/usr/bin/xfreerdp").exists()) {
            qDebug() << "xFreeRDP is installed"; ui->xfreerdp_checkBox->setChecked(true); xfreerdp_pkgs = "installed";
        } else {
            qDebug() << "xFreeRDP missing"; ui->xfreerdp_checkBox->setChecked(false); xfreerdp_pkgs = "not_present";
        }
        // XFREERDP GIT
        if (QFile("/usr/bin/xfreerdp_git").exists()) {
            qDebug() << "xFreeRDP GIT is installed"; ui->xfreerdpgit_checkBox->setChecked(true); xfreerdpgit_pkgs = "installed";
        } else {
            qDebug() << "xFreeRDP GIT missing"; ui->xfreerdpgit_checkBox->setChecked(false); xfreerdpgit_pkgs = "not_present";
        }
        // DFREERDP
        if (QFile("/usr/bin/dfreerdp").exists()) {
            qDebug() << "dFreeRDP is installed"; ui->dfreerdp_checkBox->setChecked(true); dfreerdp_pkgs = "installed";
        } else {
            qDebug() << "dFreeRDP missing"; ui->dfreerdp_checkBox->setChecked(false); dfreerdp_pkgs = "not_present";
        }
    }
    //######################START OS SERVICES CHECK######################ßß
    if (true) {
        // CUPS
        if (QFile("/usr/sbin/cupsd").exists()) {
            qDebug() << "CUPS is installed"; ui->cups_checkBox->setChecked(true); cups_pkgs = "installed";
        } else {
            qDebug() << "CUPS missing"; ui->cups_checkBox->setChecked(false); cups_pkgs = "not_present";
        }
        // X11VNC
        if (QFile("/usr/bin/x11vnc").exists()) {
            qDebug() << "X11VNC Server is installed"; ui->vnc_checkBox->setChecked(true); x11vnc_pkgs = "installed";
        } else {
            qDebug() << "X11VNC Server missing"; ui->vnc_checkBox->setChecked(false); x11vnc_pkgs = "not_present";
        }
        // SSH
        if (QFile("/usr/sbin/sshd").exists()) {
            qDebug() << "SSH Server is installed"; ui->ssh_checkBox->setChecked(true); ssh_pkgs = "installed";
        } else {
            qDebug() << "SSH Server missing"; ui->ssh_checkBox->setChecked(false); ssh_pkgs = "not_present";
        }
        // DOCKY
        if (QFile("/usr/lib/docky/Docky.exe").exists()) {
            qDebug() << "Docky is installed"; ui->docky_checkBox->setChecked(true); docky_pkgs = "installed";
        } else {
            qDebug() << "Docky missing"; ui->docky_checkBox->setChecked(false); docky_pkgs = "not_present";
        }
        // CONKY
        if (QFile("/usr/bin/conky").exists()) {
            qDebug() << "Conky is installed"; ui->conky_checkBox->setChecked(true); conky_pkgs = "installed";
        } else {
            qDebug() << "Conky missing"; ui->conky_checkBox->setChecked(false); conky_pkgs = "not_present";
        }
        // VIRTUALHERE
        if (QFile("/usr/bin/vhusbdarmpi2").exists()) {
            qDebug() << "VirtualHere USB Server is installed"; ui->virtualhere_checkBox->setChecked(true); virtualhere_pkgs = "installed";
        } else {
            qDebug() << "VirtualHere USB Server missing"; ui->virtualhere_checkBox->setChecked(false); virtualhere_pkgs = "not_present";
        }
        // OPENCONNECT
        if (QFile("/usr/lib/NetworkManager/nm-openconnect-service").exists()) {
            qDebug() << "Openconnect VPN is installed"; ui->openconnect_checkBox->setChecked(true); openconnect_pkgs = "installed";
        } else {
            qDebug() << "Openconnect VPN missing"; ui->openconnect_checkBox->setChecked(false); openconnect_pkgs = "not_present";
        }
        // OPENVPN
        if (QFile("/usr/lib/NetworkManager/nm-openvpn-service").exists()) {
            qDebug() << "OpenVPN is installed"; ui->openvpn_checkBox->setChecked(true); openvpn_pkgs = "installed";
        } else {
            qDebug() << "OpenVPN missing"; ui->openvpn_checkBox->setChecked(false); openvpn_pkgs = "not_present";
        }
        // VPNC
        if (QFile("/usr/lib/NetworkManager/nm-vpnc-service").exists()) {
            qDebug() << "VPNc is installed"; ui->vpnc_checkBox->setChecked(true); vpnc_pkgs = "installed";
        } else {
            qDebug() << "VPNc missing"; ui->vpnc_checkBox->setChecked(false); vpnc_pkgs = "not_present";
        }
        // BLUEZ
        if (QFile("/usr/bin/bluetoothctl").exists()) {
            qDebug() << "BLUEZ is installed"; ui->bluez_checkBox->setChecked(true); bluez_pkgs = "installed";
        } else {
            qDebug() << "BLUEZ missing"; ui->bluez_checkBox->setChecked(false); bluez_pkgs = "not_present";
        }
    }
    //######################START CUSTOM/OTHER SERVICES CHECK######################ßß
    if (true) {
        // OVERCLOCK
        QProcess overclock_check;
        overclock_check.start("cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq");
        overclock_check.waitForFinished(-1);
        QString overclock_stdout = overclock_check.readAllStandardOutput();
        //just check if cpu max frequency is
        if (overclock_stdout.toInt() > 900000) {
            qDebug() << "OVERCLOCK enable"; ui->overclock_checkBox->setChecked(true); overclock_pkgs = "installed";
        } else {
            qDebug() << "OVERCLOCK disable"; ui->overclock_checkBox->setChecked(false); overclock_pkgs = "not_present";
        }
        // CUSTOM1
        if (QFile(ui->customfile_lineEdit->text()).exists()) {
            qDebug() << "CUSTOM is installed"; ui->custom_checkBox->setChecked(true); custom1_pkgs = "installed";
        } else {
            qDebug() << "CUSTOM missing"; ui->custom_checkBox->setChecked(false); custom1_pkgs = "not_present";
        }
        // BLUEZ-FIRMWARE
        if (QFile("/lib/firmware/BCM2033-FW.bin").exists()) {
            qDebug() << "BLUEZ-FIRMWARE is installed"; ui->bluez_firmware_checkBox->setChecked(true); bluez_firmware_pkgs = "installed";
        } else {
            qDebug() << "BLUEZ-FIRMWARE missing"; ui->bluez_firmware_checkBox->setChecked(false); bluez_firmware_pkgs = "not_present";
        }
        // ATHEROS-FIRMWARE
        if (QFile("/lib/firmware/ar9271.fw").exists()) {
            qDebug() << "ATHEROS-FIRMWARE is installed"; ui->ath_firmware_checkBox->setChecked(true); ath_firmware_pkgs = "installed";
        } else {
            qDebug() << "ATHEROS-FIRMWARE missing"; ui->ath_firmware_checkBox->setChecked(false); ath_firmware_pkgs = "not_present";
        }
        // BCM-FIRMWARE
        if (QFile("/lib/firmware/brcm/brcmfmac43569.bin").exists()) {
            qDebug() << "BCM-FIRMWARE is installed"; ui->bcm_firmware_checkBox->setChecked(true); bcm_firmware_pkgs = "installed";
        } else {
            qDebug() << "BCM-FIRMWARE missing"; ui->bcm_firmware_checkBox->setChecked(false); bcm_firmware_pkgs = "not_present";
        }
        // INTEL-FIRMWARE
        if (QFile("/lib/firmware/ipw2200-bss.fw").exists()) {
            qDebug() << "INTEL-FIRMWARE is installed"; ui->intel_firmware_checkBox->setChecked(true); intel_firmware_pkgs = "installed";
        } else {
            qDebug() << "INTEL-FIRMWARE missing"; ui->intel_firmware_checkBox->setChecked(false); intel_firmware_pkgs = "not_present";
        }
        // REALTEK-FIRMWARE
        if (QFile("/lib/firmware/RTL8192E/boot.img").exists()) {
            qDebug() << "REALTEK-FIRMWARE is installed"; ui->rtl_firmware_checkBox->setChecked(true); rtl_firmware_pkgs = "installed";
        } else {
            qDebug() << "REALTEK-FIRMWARE missing"; ui->rtl_firmware_checkBox->setChecked(false); rtl_firmware_pkgs = "not_present";
        }
        // NG-FIRMWARE
        if (QFile("/usr/bin/linux-wlan-ng-build-firmware-deb").exists()) {
            qDebug() << "NG-FIRMWARE is installed"; ui->ng_firmware_checkBox->setChecked(true); ng_firmware_pkgs = "installed";
        } else {
            qDebug() << "NG-FIRMWARE missing"; ui->ng_firmware_checkBox->setChecked(false); ng_firmware_pkgs = "not_present";
        }
        // ZD-FIRMWARE
        if (QFile("/lib/firmware/zd1211/zd1211_ur").exists()) {
            qDebug() << "ZD-FIRMWARE is installed"; ui->zd_firmware_checkBox->setChecked(true); zd_firmware_pkgs = "installed";
        } else {
            qDebug() << "ZD-FIRMWARE missing"; ui->zd_firmware_checkBox->setChecked(false); zd_firmware_pkgs = "not_present";
        }
        // B43-FIRMWARE
        if (QFile("/lib/firmware/b43/pcm5.fw").exists()) {
            qDebug() << "B43-FIRMWARE is installed"; ui->b43_firmware_checkBox->setChecked(true); b43_firmware_pkgs = "installed";
        } else {
            qDebug() << "B43-FIRMWARE missing"; ui->b43_firmware_checkBox->setChecked(false); b43_firmware_pkgs = "not_present";
        }
        // INTERNAL BLUETOOTH
        if (QFile("/usr/bin/bluetooth-wizard").exists()) {
            qDebug() << "INTERNAL BLUETOOTH is enabled"; ui->bluetooth_checkBox->setChecked(true); int_bluetooth_pkgs = "installed";
        } else {
            qDebug() << "INTERNAL BLUETOOTH is disabled/not present"; ui->bluetooth_checkBox->setChecked(false); int_bluetooth_pkgs = "not_present";
        }
        // INTERNAL WLAN
        if (QFile("/lib/firmware/brcm/brcmfmac43430-sdio.bin").exists()) {
            qDebug() << "INTERNAL WLAN is enabled"; ui->wireless_checkBox->setChecked(true); int_wlan_pkgs = "installed";
        } else {
            qDebug() << "INTERNAL WLAN is disabled/not present"; ui->wireless_checkBox->setChecked(false); int_wlan_pkgs = "not_present";
        }
    }
}

void RPiTC::on_searchfile_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
    "",
    tr("File to check (*.*)"));
    ui->customfile_lineEdit->setText(fileName);
}

void RPiTC::on_ica_checkBox_toggled(bool checked)
{
    if (checked) {
        ui->icah264_checkBox->setEnabled(true);
    } else {
        ui->icah264_checkBox->setEnabled(false);
        ui->icah264_checkBox->setChecked(false);
    }
}
