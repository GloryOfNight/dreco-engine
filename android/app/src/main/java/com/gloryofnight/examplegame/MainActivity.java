package com.gloryofnight.examplegame;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import org.libsdl.app.SDLActivity;

public class MainActivity extends SDLActivity
{
    @Override
    protected String getMainFunction() {
        return "android_main";
    }

    @Override
    protected String[] getLibraries() {
        return new String[]{
                "hidapi",
                "SDL2",
                "SDL2_image",
                "SDL2_mixer",
                "dreco-engine",
                "example-game"
        };
    }
}
