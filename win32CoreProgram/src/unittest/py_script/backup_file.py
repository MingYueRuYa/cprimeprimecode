# -*- coding: utf-8 -*-

import hashlib
import os
import shutil
import time
import smtplib
import socket

from email.mime.text import MIMEText
from email.header import Header

success_copy = []
failed_copy = []


def md5check(filename):
    m = hashlib.md5()
    # 以二进制的方式打开文件
    with open(filename, 'rb') as f:
        while True:
            # 只读取前面4字节
            data = f.read(4096)
            if not data:
                break
            m.update(data)
    return m.hexdigest()


def copy(path):
    new_path = path
    new_path = new_path.replace(old_source, new_source)
    # print(new_path)
    # 如果是个文件类型，则需要比较md5值
    if os.path.isfile(new_path):
        old_md5 = md5check(path)
        new_md5 = md5check(new_path)
        # md5一致则说明文件没有变化，不需要copy
        if old_md5 != new_md5:
            try:
                shutil.copy(path, new_path)
                success_copy.append(path)
            except:
                failed_copy.append(path)
    # 如果是文件夹，则需要创建文件夹
    else:
        dirname = os.path.dirname(new_path)
        if os.path.exists(dirname):
            shutil.copy(path, new_path)
            success_copy.append(path)
        else:  # 目录不存在，则直接创建目录并复制文件
            try:
                os.makedirs(dirname)
                shutil.copy(path, new_path)
            except WindowsError:
                failed_copy.append("create dir failed:" + path)


# 查找所有目录文件的递归函数
def lsdir(folders):
    path = os.listdir(folders)
    for line in path:
        line = folders + '/' + line
        if os.path.isdir(line):
            lsdir(line)
        else:
            copy(line)


def send_mail():
    if len(success_copy) == 0 and len(failed_copy) == 0:
        return

    # 获取本机电脑名
    hostname = socket.getfqdn(socket.gethostname())
    # 获取本机ip
    hostaddr = socket.gethostbyname(hostname)

    # 第三方 SMTP 服务
    mail_host = "smtp.163.com"  # 设置服务器
    mail_user = "liushixiongcpp@163.com"  # 用户名
    mail_pass = "liushi1219"  # 口令

    sender = mail_user
    # 接收邮件，可设置为你的QQ邮箱或者其他邮箱
    receivers = [sender, '635672377@qq.com']
    success_info_msg = ""
    if len(success_copy) != 0:
        success_info_msg = "Successfully backing up files:\r\n"
        for item in success_copy:
            # print(count + ":" + item)
            success_info_msg += item + "\r\n"
        success_info_msg += "--------------------------------------\r\n"

    if len(failed_copy) != 0:
        success_info_msg = "Backup file failed:\r\n"
        for item in failed_copy:
            # print(count + ":" + item)
            success_info_msg += item + "\r\n"

    success_info_msg += hostname + "\r\n"
    success_info_msg += hostaddr + "\r\n"

    message = MIMEText(success_info_msg, 'plain', 'utf-8')
    message['From'] = sender
    message['To'] = "635672377@qq.com"

    subject = '文件备份'
    message['Subject'] = Header(subject, 'utf-8')

    try:
        smtpObj = smtplib.SMTP()
        # 调试的时候可以打开，如果出错了一定要把调试信息打开便于调试，不至于无处下手
        # smtpObj.set_debuglevel(1)
        smtpObj.connect(mail_host)  # 25 为 SMTP 端口号
        smtpObj.login(mail_user, mail_pass)
        smtpObj.sendmail(sender, receivers, message.as_string())
        print("邮件发送成功")
    # except smtplib.SMTPException:
    except:
        print("Error: 无法发送邮件")


if __name__ == '__main__':
    print("start back up file...")
    global old_source
    global new_source
    # 需要备份的目录，备份到新目录
    old_source = "G:/code/code_git/xmind"
    new_source = "F:/13_bak"
    lsdir(old_source)

    count = 1
    if len(success_copy) != 0:
        for item in success_copy:
            # print(count + ":" + item)
            print("{0} {1}".format(count, item))
            count += 1
    else:
        print("back file empty.")

    print("---------------------------------------------")

    count = 1
    if len(failed_copy) != 0:
        for item in failed_copy:
            print("{0} {1}".format(count, item))
            count += 1
    else:
        print("back file error empty.")
    print("---------------------------------------------")

    print("back up file finished...")

    send_mail()

    # 倒计时3s在关闭控制台窗口
    count = 3
    while count < 0:
        time.sleep(1)
        count -= 1
