# Embedded Programming practical work repository

This repository contains the description of the labs for the Embedded Programming course of EMSE TB3 PWME, M1 CPS2.

## Order of the labs

1. [`lab_testing_electronic_components.adoc`](lab_testing_electronic_components.adoc)
2. [`lab_iot_module.adoc`](lab_iot_module.adoc)
3. ...

## How to use this project

### Set up

The first thing you need to do is to clone your project, and merge this branch into your repository.

Assume your group is #1

```
group=1
```

1. clone your project

```
git clone git@gitlab.emse.fr:isi/enseignements/m-info/iot/groups/$group.git
```

or if you haven't yet added a SSH key for secure access to GitLab ([learn more](https://gitlab.emse.fr/help/user/ssh.md)):

```
git clone https://gitlab.emse.fr/isi/enseignements/m-info/iot/groups/$group.git
```

2. `cd` to your project folder

3. add this project as the `labs` remote, and fetch it.

```
git remote add labs git@gitlab.emse.fr:cps2/pcd/labs.git
git fetch labs
```

or 

```
git remote add labs https://gitlab.emse.fr/cps2/pcd/labs.git
git fetch labs
```

4. merge `labs/2023` into your `main` branch

```
git merge labs/2023
```

Now your `main` branch is in sync with this version. You can directly edit the **adoc** documents, commit with informative messages, and push your changes. 

### Update

The professor may add new labs or update the existing labs. To merge these changes to your project, you need to pull `labs/2023` (= fetch and merge). 

```
git pull labs/2023
```

