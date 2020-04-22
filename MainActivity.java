package com.example.iotfirebase;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;

import android.widget.ToggleButton;
import android.widget.CompoundButton;

//import android.widget.CompoundButton;
import android.widget.TextView;
//import android.widget.ToggleButton;


import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {

    ToggleButton buttonLedTest;
    String valueJoystick;
    String valueLdr;
    String valueLed1;
    String valueLed2;
    String valueLedTest;
    TextView joystick;
    TextView ldr;
    TextView led1;
    TextView led2;
    TextView ledTest;

    DatabaseReference dref;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        buttonLedTest = (ToggleButton) findViewById(R.id.toggleButton_ledTest);
        ldr = (TextView) findViewById(R.id.ldr);
        joystick = (TextView) findViewById(R.id.joystick);
        led1 = (TextView) findViewById(R.id.led1);
        led2 = (TextView) findViewById(R.id.led2);
        ledTest = (TextView) findViewById(R.id.ledTest);


        dref = FirebaseDatabase.getInstance().getReference();
        dref.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {

                valueLdr = dataSnapshot.child("node1/ldr").getValue().toString();
                ldr.setText(valueLdr);

                valueJoystick = dataSnapshot.child("node1/joystick").getValue().toString();
                joystick.setText(valueJoystick);

                valueLed1 = dataSnapshot.child("node1/led1").getValue().toString();
                led1.setText(valueLed1);

                valueLed2 = dataSnapshot.child("node1/led2").getValue().toString();
                led2.setText(valueLed2);

                valueLedTest = dataSnapshot.child("node1/ledTest").getValue().toString();
                ledTest.setText(valueLedTest);
                if(valueLedTest.equals("0"))
                    buttonLedTest.setChecked(false);
                else
                    buttonLedTest.setChecked(true);

            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        buttonLedTest.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    DatabaseReference ledTestRef = FirebaseDatabase.getInstance().getReference("node1/ledTest");
                    ledTestRef.setValue(1);
                }
                else
                {
                    DatabaseReference ledTestRef = FirebaseDatabase.getInstance().getReference("node1/ledTest");
                    ledTestRef.setValue(0);
                }
            }
        });


    }
}
