using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class FilePathList : ScriptableObject
{
    static public FilePathList CreateMyAssets(string objectName)
    {
        FilePathList so = ScriptableObject.CreateInstance<FilePathList>();
        AssetDatabase.CreateAsset(so,"Assets/" + objectName);
        return so;
    }
    public List<string> data;
}
