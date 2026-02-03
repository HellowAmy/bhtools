"""
更新VSCode的快捷启动文件
"""

import os


#
def get_file_lines(file_path):
    with open(file_path, "r", encoding="utf-8") as f:
        lines = f.readlines()
    return lines


#
def get_all_filenames(directory):
    items = os.listdir(directory)
    files = [
        os.path.splitext(f)[0]
        for f in items
        if os.path.isfile(os.path.join(directory, f))
    ]
    files.sort()
    return files


#
def find_flag_range(lines):
    ret_lines = []
    start = False
    for line in lines:
        pos = line.find("+++++")
        if pos != -1:
            break
        if start == True:
            ret_lines.append(line)
        pos = line.find("=====")
        if pos != -1:
            start = True
    ret_lines = [line.replace("//", "", 1).strip() for line in ret_lines]
    return "".join(ret_lines)


#
def remove_flag_range(lines):
    posb = -1
    pose = -1
    for i, line in enumerate(lines):
        pos = line.find("+++++")
        if pos != -1:
            posb = i

        pos = line.find("-----")
        if pos != -1:
            pose = i

        if posb != -1 and pose != -1:
            del lines[posb + 1 : pose]
            return


#
def insert_flag_lines(lines, str):
    remove_flag_range(lines)
    for i, line in enumerate(lines):
        pos = line.find("+++++")
        if pos != -1:
            lines.insert(i + 1, str)
            return "".join(lines)


#
def save_to_file(content, file_path):
    with open(file_path, "w", encoding="utf-8") as f:
        f.write(content)


# 主函数
if __name__ == "__main__":
    print("< 更新开始 >")

    #
    file_launch = os.path.dirname(os.path.abspath(__file__)) + "/../.vscode/launch.json"
    file_tasks = os.path.dirname(os.path.abspath(__file__)) + "/../.vscode/tasks.json"
    path_test = os.path.dirname(os.path.abspath(__file__)) + "/../test"

    #
    ls_launch = get_file_lines(file_launch)
    ls_tasks = get_file_lines(file_tasks)
    ls_filename = get_all_filenames(path_test)
    print(ls_filename)

    #
    str_flag = find_flag_range(ls_launch)
    str_all = ""
    for i, name in enumerate(ls_filename):
        str = str_flag.replace("##NAME##", name)
        str_all += str
        if i != len(ls_filename) - 1:
            str_all += ","
    str_all += "\n"
    str_launch = insert_flag_lines(ls_launch, str_all)
    save_to_file(str_launch, file_launch)

    #
    str_flag = find_flag_range(ls_tasks)
    str_all = ""
    for i, name in enumerate(ls_filename):
        str = str_flag.replace("##NAME##", name)
        str_all += str
        if i != len(ls_filename) - 1:
            str_all += ","
    str_all += "\n"
    str_tasks = insert_flag_lines(ls_tasks, str_all)
    save_to_file(str_tasks, file_tasks)

    print("< 更新完成 >")
