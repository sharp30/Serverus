import re

EMAIL_TEMPLATE = "^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$"
USERNAME_TEMPLATE = "/^[a-zA-Z0-9]{5,30}+$/"
PASSWORD_TEMPLATE = "^(?=.*[^a-zA-Z]).{8,40}$"


def validate_input(username, password, email="valid@gmail.com"):
    try:
        valid_email = re.search(EMAIL_TEMPLATE, email)
        valid_username = re.search(USERNAME_TEMPLATE, username)
        valid_password = re.search(PASSWORD_TEMPLATE, password)
    except Exception as e:
        return False

    return valid_email and valid_password and valid_username
